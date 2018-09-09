/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_validation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <eyevresh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 15:47:00 by eyevresh          #+#    #+#             */
/*   Updated: 2018/09/02 15:47:00 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

t_instruction	get_instruction(const char *line)
{
	t_instruction instruction;

	if (ft_strnequ(line, "live", 4) || ft_strnequ(line, "ld", 2))
		instruction = ft_strnequ(line, "live", 4) ? e_live : e_ld;
	else if (ft_strnequ(line, "st", 2) || ft_strnequ(line, "add", 3))
		instruction = ft_strnequ(line, "st", 2) ? e_st : e_add;
	else if (ft_strnequ(line, "sub", 3) || ft_strnequ(line, "and", 3))
		instruction = ft_strnequ(line, "sub", 3) ? e_sub : e_and;
	else if (ft_strnequ(line, "or", 2) || ft_strnequ(line, "xor", 3))
		instruction = ft_strnequ(line, "or", 2) ? e_or : e_xor;
	else if (ft_strnequ(line, "zjmp", 4) || ft_strnequ(line, "ldi", 3))
		instruction = ft_strnequ(line, "zjmp", 4) ? e_zjmp : e_ldi;
	else if (ft_strnequ(line, "sti", 3) || ft_strnequ(line, "fork", 4))
		instruction = ft_strnequ(line, "sti", 3) ? e_sti : e_fork;
	else if (ft_strnequ(line, "lld", 3) || ft_strnequ(line, "lldi", 4))
		instruction = ft_strnequ(line, "lld", 3) ? e_lld : e_lldi;
	else if (ft_strnequ(line, "lfork", 5) || ft_strnequ(line, "aff", 3))
		instruction = ft_strnequ(line, "lfork", 5) ? e_lfork : e_aff;
	else
		instruction = not_instruction;
	return (instruction);
}

void			handle_live_instruction(t_db *db, const char *instruction)
{
	instruction += 4;
	while (ft_iswhitespace(*instruction))
		++instruction;
	if (*instruction != '%')
		clean_and_exit(db, "WRONG ARGUMENT IN LIVE INSTRUCTION");
	++instruction;
	if (*instruction != ':' && *instruction != '-' && !ft_isdigit(*instruction))
		clean_and_exit(db, "ARGUMENT SYNTAX ERROR IN LIVE INSTRUCTION");
	allocate_new_instruction(db);
	db->bot.instructions[db->instructions_counter - 1].type = e_live;
	db->bot.instructions[db->instructions_counter - 1].arguments_count = 1;
	db->bot.instructions[db->instructions_counter - 1].size = 5;
	db->bot.instructions[db->instructions_counter - 1].codage = 0;
	instruction += handle_direct_argument(db, instruction, 1);
}
