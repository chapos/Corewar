/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 15:02:27 by eyevresh          #+#    #+#             */
/*   Updated: 2018/09/24 18:33:17 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

static int	open_source_file(t_db *db, const char *file_name)
{
	int fd;

	fd = open(file_name, O_DIRECTORY);
	if (fd != -1)
		clean_and_exit(db, "DIRECTORIES AREN'T ALLOWED");
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
	fd = open(new_name, O_CREAT | O_RDWR | O_TRUNC, 400);
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
	db->bot.magic_header = big_little_endian(0xea83f3, true);
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
	db->v_data.chars_counter = 0;
}

int			main(int argc, char **argv)
{
	t_db	db;

	if (argc < 2)
	{
		ft_putstr_fd(USAGE, STDERR_FILENO);
		exit(0);
	}
	db.arithmetic = ft_strequ(argv[1], "-a") ? true : false;
	check_file_name(argv[argc - 1]);
	init_db(&db);
	db.source_fd = open_source_file(&db, argv[argc - 1]);
	read_source_file(&db);
	db.output_fd = create_output_file(argv[argc - 1]);
	write_result(&db, argv[argc - 1]);
	clean_and_exit(&db, NULL);
	return (0);
}
