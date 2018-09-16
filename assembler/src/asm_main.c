/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 15:02:27 by eyevresh          #+#    #+#             */
/*   Updated: 2018/08/18 15:02:38 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

static int	open_source_file(const char *file_name)
{
	int fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd(OPEN_SOURCE_ERR, STDERR_FILENO);
		ft_putstr_fd(file_name, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		exit(0);
	}
	return (fd);
}

static int	create_output_file(char *file_name)
{
	int		fd;
	char	*name_offset;
	char	*new_name;

	name_offset = ft_strrchr(file_name, '.');
	*name_offset = '\0';
	new_name = ft_strjoin(file_name, ".cor");
	fd = open(new_name, O_CREAT | O_RDWR, 400);
	if (fd == -1)
	{
		ft_putstr_fd(OPEN_OUTPUT_ERR, STDERR_FILENO);
		ft_putstr_fd(new_name, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		ft_strdel(&new_name);
		exit(0);
	}
	ft_strdel(&new_name);
	return (fd);
}

static void	check_file_name(const char *file_name)
{
	const char *name_offset;

	name_offset = ft_strrchr(file_name, '.');
	if (name_offset == NULL || ft_strlen(name_offset) != 2
		|| name_offset[1] != 's')
	{
		ft_putstr_fd(FILE_NAME_ERR, STDERR_FILENO);
		exit(0);
	}
}

static void	init_db(t_db *db)
{
	ft_bzero(db->bot.buff, COMMENT_LENGTH);
	db->bot.magic_header = big_little_endian(0xea83f3);
	db->bot.separator = 0x0;
	db->bot.bot_name = NULL;
	db->bot.bot_comment = NULL;
	db->bot.bot_size = 0;
	db->bot.instructions = NULL;
	db->inst_counter = 0;
	db->labels = NULL;
	db->labels_counter = 0;
	db->output_fd = 0;
	db->source_fd = 0;
	db->v_data.line_counter = 0;
	db->v_data.name_readed = false;
	db->v_data.comment_readed = false;
	db->v_data.line = NULL;
	db->v_data.name_size = 0;
	db->v_data.comment_size = 0;
	db->v_data.multiline_string = false;
	db->v_data.last_line_is_insturction = false;
}

void		print_labels(t_db *db)
{
	size_t i;

	i = 0;
	while (i < db->labels_counter)
	{
		ft_printf("%s: %u\n", db->labels[i].name, db->labels[i].bytes_position);
		++i;
	}
}

void		write_instructions(t_db *db)
{
	size_t	i;

	i = 0;
	while (i < db->inst_counter)
	{
		write(db->output_fd, &db->bot.instructions[i].type, sizeof(uint8_t));
		write(db->output_fd, &db->bot.instructions[i].args[0].value,
				sizeof(uint32_t));
		++i;
	}
}

int			main(int argc, char **argv)
{
	t_db	db;

	if (argc < 2)
	{
		ft_putstr_fd(USAGE, STDERR_FILENO);
		exit(0);
	}
	check_file_name(argv[argc - 1]);
	init_db(&db);
	db.source_fd = open_source_file(argv[argc - 1]);
	db.output_fd = create_output_file(argv[argc - 1]);
	read_source_file(&db);
	write(db.output_fd, &db.bot.magic_header, sizeof(uint32_t));
	write(db.output_fd, db.bot.bot_name, db.v_data.name_size);
	write(db.output_fd, db.bot.buff, PROG_NAME_LENGTH - db.v_data.name_size);
	write(db.output_fd, &db.bot.separator, sizeof(uint32_t));
	write(db.output_fd, &db.bot.separator, sizeof(uint32_t));
	write(db.output_fd, db.bot.bot_comment, db.v_data.comment_size);
	write(db.output_fd, db.bot.buff, COMMENT_LENGTH - db.v_data.comment_size);
	write(db.output_fd, &db.bot.separator, sizeof(uint32_t));
	write_instructions(&db);
	//print_labels(&db);
	clean_and_exit(&db, NULL);
	return (0);
}
