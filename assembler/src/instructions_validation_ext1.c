/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_validation_ext1.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <eyevresh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 15:06:00 by eyevresh          #+#    #+#             */
/*   Updated: 2018/09/22 15:06:00 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

void		handle_st_instruction(t_db *db, const char *inst)
{
	allocate_new_instruction(db);
	db->bot.instructions[db->inst_counter - 1].type = e_st;
	db->bot.instructions[db->inst_counter - 1].arguments_count = 2;
	inst = skip_whitespaces(inst);
	inst += handle_register_argument(db, inst, 1);
	inst = skip_whitespaces(inst);
	if (*inst != ',')
		clean_and_exit(db, "THERE IS NO 2nd ARGUMENT IN ST INSTRUCTION");
	++inst;
	inst = skip_whitespaces(inst);
	if (*inst != 'r' && *inst != '-'
		&& *inst != ':' && !ft_isdigit(*inst))
		clean_and_exit(db, "WRONG 2nd ARGUMENT IN ST INSTRUCTION");
	inst += *inst == 'r' ? handle_register_argument(db, inst, 2)
			: handle_indirect_argument(db, inst, 2);
	while (ft_isdigit(*inst))
		++inst;
	inst = skip_whitespaces(inst);
	if (*inst != '\0' && *inst != ';' && *inst != '#')
		clean_and_exit(db, "ST INSTRUCTION SYNTAX ERROR");
	db->bot.instructions[db->inst_counter - 1].instruction_size =
			calc_codage_and_instruction_size(db) + 2;
	db->bot.bot_size += (calc_codage_and_instruction_size(db) + 2);
}

void		handle_add_instruction(t_db *db, const char *inst)
{
	allocate_new_instruction(db);
	db->bot.instructions[db->inst_counter - 1].type = e_add;
	db->bot.instructions[db->inst_counter - 1].arguments_count = 3;
	inst = skip_whitespaces(inst);
	inst += handle_register_argument(db, inst, 1);
	inst = skip_whitespaces(inst);
	if (*inst != ',')
		clean_and_exit(db, "THERE IS NO 2nd ARGUMENT IN ADD INSTRUCTION");
	++inst;
	inst = skip_whitespaces(inst);
	inst += handle_register_argument(db, inst, 2);
	inst = skip_whitespaces(inst);
	if (*inst != ',')
		clean_and_exit(db, "THERE IS NO 3rd ARGUMENT IN ADD INSTRUCTION");
	++inst;
	inst = skip_whitespaces(inst);
	inst += handle_register_argument(db, inst, 3);
	inst = skip_whitespaces(inst);
	if (*inst != '\0' && *inst != ';' && *inst != '#')
		clean_and_exit(db, "ADD INSTRUCTION SYNTAX ERROR");
	db->bot.instructions[db->inst_counter - 1].instruction_size =
			calc_codage_and_instruction_size(db) + 2;
	db->bot.bot_size += (calc_codage_and_instruction_size(db) + 2);
}

void		handle_sub_instruction(t_db *db, const char *inst)
{
	allocate_new_instruction(db);
	db->bot.instructions[db->inst_counter - 1].type = e_sub;
	db->bot.instructions[db->inst_counter - 1].arguments_count = 3;
	inst = skip_whitespaces(inst);
	inst += handle_register_argument(db, inst, 1);
	inst = skip_whitespaces(inst);
	if (*inst != ',')
		clean_and_exit(db, "THERE IS NO 2nd ARGUMENT IN SUB INSTRUCTION");
	++inst;
	inst = skip_whitespaces(inst);
	inst += handle_register_argument(db, inst, 2);
	inst = skip_whitespaces(inst);
	if (*inst != ',')
		clean_and_exit(db, "THERE IS NO 3rd ARGUMENT IN SUB INSTRUCTION");
	++inst;
	inst = skip_whitespaces(inst);
	inst += handle_register_argument(db, inst, 3);
	inst = skip_whitespaces(inst);
	if (*inst != '\0' && *inst != ';' && *inst != '#')
		clean_and_exit(db, "SUB INSTRUCTION SYNTAX ERROR");
	db->bot.instructions[db->inst_counter - 1].instruction_size =
			calc_codage_and_instruction_size(db) + 2;
	db->bot.bot_size += (calc_codage_and_instruction_size(db) + 2);
}

static void	and_or_xor_extended(t_db *db, const char *inst)
{
	if (*inst != 'r' && *inst != '-' && *inst != ':'
		&& !ft_isdigit(*inst) && *inst != '%')
		clean_and_exit(db, "WRONG 2nd ARGUMENT IN AND/OR/XOR INSTRUCTION");
	if (*inst == 'r')
		inst += handle_register_argument(db, inst, 2);
	else if (*inst == '%')
		inst += (handle_direct_argument(db, inst + 1, 2) + 1);
	else
		inst += handle_indirect_argument(db, inst, 2);
	while (ft_isdigit(*inst))
		++inst;
	inst = skip_whitespaces(inst);
	if (*inst != ',')
		clean_and_exit(db, "THERE IS NO 3rd ARGUMENT IN AND/OR/XOR INSTRUCT");
	++inst;
	inst = skip_whitespaces(inst);
	inst += handle_register_argument(db, inst, 3);
	inst = skip_whitespaces(inst);
	if (*inst != '\0' && *inst != ';' && *inst != '#')
		clean_and_exit(db, "ANX/OR/XOR INSTRUCTION SYNTAX ERROR");
	db->bot.instructions[db->inst_counter - 1].instruction_size =
			calc_codage_and_instruction_size(db) + 2;
	db->bot.bot_size += (calc_codage_and_instruction_size(db) + 2);
}

void		handle_and_or_xor_instruction(t_db *db, const char *inst,
			t_instruction type)
{
	allocate_new_instruction(db);
	db->bot.instructions[db->inst_counter - 1].type = type;
	db->bot.instructions[db->inst_counter - 1].arguments_count = 3;
	inst = skip_whitespaces(inst);
	if (*inst != 'r' && *inst != '-' && *inst != ':'
		&& !ft_isdigit(*inst) && *inst != '%')
		clean_and_exit(db, "WRONG 1st ARGUMENT IN AND/OR/XOR INSTRUCTION");
	if (*inst == 'r')
		inst += handle_register_argument(db, inst, 1);
	else if (*inst == '%')
		inst += (handle_direct_argument(db, inst + 1, 1) + 1);
	else
		inst += handle_indirect_argument(db, inst, 1);
	while (ft_isdigit(*inst))
		++inst;
	inst = skip_whitespaces(inst);
	if (*inst != ',')
		clean_and_exit(db, "THERE IS NO 2nd ARGUMENT IN AND/OR/XOR INSTRUCT");
	++inst;
	inst = skip_whitespaces(inst);
	and_or_xor_extended(db, inst);
}
