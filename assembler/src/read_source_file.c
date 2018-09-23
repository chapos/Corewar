/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_source_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <eyevresh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 17:03:00 by eyevresh          #+#    #+#             */
/*   Updated: 2018/08/19 17:03:00 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

static void	validate_and_save_instruction(t_db *db, char *instruction)
{
	if (get_instruction(instruction) == e_live)
		handle_live_instruction(db, instruction);
	else if (get_instruction(instruction) == e_ldi)
		handle_ldi_lldi_instruction(db, instruction + 3, e_ldi);
	else if (get_instruction(instruction) == e_lldi)
		handle_ldi_lldi_instruction(db, instruction + 4, e_lldi);
	else if (get_instruction(instruction) == e_ld)
		handle_ld_lld_instruction(db, instruction + 2, e_ld);
	else if (get_instruction(instruction) == e_st)
		handle_st_instruction(db, instruction + 2);
	else if (get_instruction(instruction) == e_add)
		handle_add_instruction(db, instruction + 3);
	else if (get_instruction(instruction) == e_sub)
		handle_sub_instruction(db, instruction + 3);
	else
		validate_and_save_instruction_ext(db, instruction);
}

static void	validate_line_extended(t_db *db)
{
	char	*tmp;
	size_t	count;

	tmp = db->v_data.line;
	count = 0;
	while (ft_strchr(LABEL_CHARS, db->v_data.line[count]))
		++count;
	if (tmp[count] == ':')
		tmp += validate_and_save_lable(db);
	while (ft_iswhitespace(*tmp))
		++tmp;
	if (*tmp == ';' || *tmp == '#' || *tmp == '\0')
		return ;
	if (get_instruction(tmp) == not_instruction)
		clean_and_exit(db, "LABEL/INSTRUCTION SYNTAX ERROR");
	validate_and_save_instruction(db, tmp);
}

static void	validate_line(t_db *db)
{
	char *tmp;

	tmp = db->v_data.line;
	db->v_data.line = ft_strtrim(tmp);
	ft_strdel(&tmp);
	if (db->v_data.line[0] == '#' || db->v_data.line[0] == ';'
			|| ft_strequ(db->v_data.line, ""))
		return ;
	else if (ft_strnequ(db->v_data.line, ".name", 5))
		clean_and_exit(db, "THERE IS ALREADY ONE NAME");
	else if (ft_strnequ(db->v_data.line, ".comment", 8))
		clean_and_exit(db, "THERE IS ALREADY ONE COMMENT");
	validate_line_extended(db);
}

static void	read_instructions(t_db *db)
{
	int	gnl_ret_val;

	while ((gnl_ret_val = get_next_line(db->source_fd, &db->v_data.line)))
	{
		db->v_data.chars_counter += (ft_strlen(db->v_data.line) + 1);
		++db->v_data.line_counter;
		if (gnl_ret_val == -1)
			clean_and_exit(db, "READING ERROR");
		else if (ft_strequ(db->v_data.line, ""))
			;
		else
			validate_line(db);
		ft_strdel(&db->v_data.line);
	}
	lseek(db->source_fd, db->v_data.chars_counter - 1, SEEK_SET);
	db->v_data.line = ft_strnew(1);
	read(db->source_fd, db->v_data.line, 1);
	if (db->v_data.line[0] != '\n')
		clean_and_exit(db, "NO END LINE");
	if (db->bot.bot_size == 0)
		clean_and_exit(db, "THERE IS 0 INSTRUCTIONS");
}

void		read_source_file(t_db *db)
{
	read_name_and_comment(db);
	read_instructions(db);
	set_labels_to_instructions(db);
	if (db->arithmetic)
		do_calculation(db);
	db->bot.bot_size = big_little_endian(db->bot.bot_size, true);
}
