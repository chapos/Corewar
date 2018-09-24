/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writing_result.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <eyevresh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 11:16:00 by eyevresh          #+#    #+#             */
/*   Updated: 2018/09/22 11:16:00 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

static void	write_instructions(t_db *db)
{
	int i;
	int j;

	i = -1;
	while (++i < (int)db->inst_counter)
	{
		write(db->output_fd, &db->bot.instructions[i].type, sizeof(uint8_t));
		if (db->bot.instructions[i].codage != 0)
			write(db->output_fd, &db->bot.instructions[i].codage,
				sizeof(uint8_t));
		j = -1;
		while (++j < (int)db->bot.instructions[i].arguments_count)
		{
			if (db->bot.instructions[i].args[j].type == e_register)
				write(db->output_fd, &db->bot.instructions[i].args[j].value,
					sizeof(uint8_t));
			else if (db->bot.instructions[i].args[j].type == e_undirect)
				write(db->output_fd, &db->bot.instructions[i].args[j].value,
					sizeof(uint16_t));
			else
				write(db->output_fd, &db->bot.instructions[i].args[j].value,
				get_direct_arg_size_by_name(db->bot.instructions[i].type));
		}
	}
}

static void	print_to_stdout(char *file_name)
{
	char	*new_name;

	new_name = ft_strjoin(file_name, ".cor");
	ft_putstr("Writing output program to ");
	ft_putstr(new_name);
	ft_putchar('\n');
	ft_strdel(&new_name);
}

void		write_result(t_db *db, char *file_name)
{
	write(db->output_fd, &db->bot.magic_header, sizeof(uint32_t));
	write(db->output_fd, db->bot.bot_name, db->v_data.name_size);
	write(db->output_fd, db->bot.buff, PROG_NAME_LENGTH - db->v_data.name_size);
	write(db->output_fd, &db->bot.separator, sizeof(uint32_t));
	write(db->output_fd, &db->bot.bot_size, sizeof(uint32_t));
	write(db->output_fd, db->bot.bot_comment, db->v_data.comment_size);
	write(db->output_fd, db->bot.buff, COMMENT_LENGTH
		- db->v_data.comment_size);
	write(db->output_fd, &db->bot.separator, sizeof(uint32_t));
	write_instructions(db);
	print_to_stdout(file_name);
}
