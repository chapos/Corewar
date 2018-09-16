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
		clean_and_exit(db, "WRONG 1st ARGUMENT IN LIVE INSTRUCTION");
	++instruction;
	allocate_new_instruction(db);
	db->bot.instructions[db->inst_counter - 1].type = e_live;
	db->bot.instructions[db->inst_counter - 1].arguments_count = 1;
	instruction += handle_direct_argument(db, instruction, 1);
	while (ft_isdigit(*instruction))
		++instruction;
	while (ft_iswhitespace(*instruction))
		++instruction;
	if (*instruction != '\0' && *instruction != ';' && *instruction != '#')
		clean_and_exit(db, "LIVE INSTRUCTION SYNTAX ERROR");
	db->bot.bot_size += 5;
}

void			handle_ld_instruction(t_db *db, const char *inst)
{
	inst += 2;
	while (ft_iswhitespace(*inst))
		++inst;
	if (*inst != '%' && *inst != '-'
		&& *inst != ':' && !ft_isdigit(*inst))
		clean_and_exit(db, "WRONG 1st ARGUMENT IN LD INSTRUCTION");
	allocate_new_instruction(db);
	db->bot.instructions[db->inst_counter - 1].type = e_ld;
	db->bot.instructions[db->inst_counter - 1].arguments_count = 2;
	inst += *inst == '%' ? handle_direct_argument(db, ++inst, 1) :
			handle_indirect_argument(db, inst, 1);
	while (ft_isdigit(*inst))
		++inst;
	while (ft_iswhitespace(*inst))
		++inst;
	if (*inst != ',')
		clean_and_exit(db, "THERE IS NO 2nd ARGUMENT IN LD INSTRUCTION");
	inst += handle_register_argument(db, inst + 1, 2);
	while (ft_iswhitespace(*inst))
		++inst;
	if (*inst != '\0' && *inst != ';' && *inst != '#')
		clean_and_exit(db, "LD INSTRUCTION SYNTAX ERROR");
	//TODO:: codage
	//TODO:: count bytes size of this instruction
	//TODO:: write proper instructions writing to the file
}
