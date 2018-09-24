/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_validation_ext2.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <eyevresh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 10:44:00 by eyevresh          #+#    #+#             */
/*   Updated: 2018/09/23 10:44:00 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

void		handle_zjmp_instruction(t_db *db, const char *inst)
{
	allocate_new_instruction(db);
	db->bot.instructions[db->inst_counter - 1].type = e_zjmp;
	db->bot.instructions[db->inst_counter - 1].arguments_count = 1;
	inst = skip_whitespaces(inst);
	if (*inst != '%')
		clean_and_exit(db, "WRONG 1st ARGUMENT IN ZJMP INSTRUCTION");
	++inst;
	inst += handle_direct_argument(db, inst, 1);
	while (ft_isdigit(*inst))
		++inst;
	inst = skip_whitespaces(inst);
	if (*inst != '\0' && *inst != ';' && *inst != '#')
		clean_and_exit(db, "ZJMP INSTRUCTION SYNTAX ERROR");
	db->bot.instructions[db->inst_counter - 1].instruction_size = 3;
	db->bot.bot_size += 3;
}

static void	ldi_lldi_extended(t_db *db, const char *inst)
{
	if (*inst != 'r' && *inst != '%')
		clean_and_exit(db, "WRONG 2nd ARGUMENT IN LDI/LLDI INSTRUCTION");
	inst += *inst == 'r' ? handle_register_argument(db, inst, 2) :
			(handle_direct_argument(db, inst + 1, 2) + 1);
	while (ft_isdigit(*inst))
		++inst;
	inst = skip_whitespaces(inst);
	if (*inst != ',')
		clean_and_exit(db, "THERE IS NO 3rd ARGUMENT IN LDI/LLDI INSTRUCTION");
	++inst;
	inst = skip_whitespaces(inst);
	inst += handle_register_argument(db, inst, 3);
	inst = skip_whitespaces(inst);
	if (*inst != '\0' && *inst != ';' && *inst != '#')
		clean_and_exit(db, "LDI/LLDI INSTRUCTION SYNTAX ERROR");
	db->bot.instructions[db->inst_counter - 1].instruction_size =
			calc_codage_and_instruction_size(db) + 2;
	db->bot.bot_size += (calc_codage_and_instruction_size(db) + 2);
}

void		handle_ldi_lldi_instruction(t_db *db, const char *inst,
										t_instruction type)
{
	allocate_new_instruction(db);
	db->bot.instructions[db->inst_counter - 1].type = type;
	db->bot.instructions[db->inst_counter - 1].arguments_count = 3;
	inst = skip_whitespaces(inst);
	if (*inst != 'r' && *inst != '-' && *inst != ':'
		&& !ft_isdigit(*inst) && *inst != '%')
		clean_and_exit(db, "WRONG 1st ARGUMENT IN LDI/LLDI INSTRUCTION");
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
		clean_and_exit(db, "THERE IS NO 2nd ARGUMENT IN LDI/LLDI INSTRUCTION");
	++inst;
	inst = skip_whitespaces(inst);
	ldi_lldi_extended(db, inst);
}

static void	sti_extended(t_db *db, const char *inst)
{
	if (*inst != ',')
		clean_and_exit(db, "THERE IS NO 3rd ARGUMENT IN STI INSTRUCTION");
	++inst;
	inst = skip_whitespaces(inst);
	if (*inst != 'r' && *inst != '%')
		clean_and_exit(db, "WRONG 3rd ARGUMENT IN STI INSTRUCTION");
	inst += *inst == 'r' ? handle_register_argument(db, inst, 3) :
			(handle_direct_argument(db, inst + 1, 3) + 1);
	while (ft_isdigit(*inst))
		++inst;
	inst = skip_whitespaces(inst);
	if (*inst != '\0' && *inst != ';' && *inst != '#')
		clean_and_exit(db, "STI INSTRUCTION SYNTAX ERROR");
	db->bot.instructions[db->inst_counter - 1].instruction_size =
			calc_codage_and_instruction_size(db) + 2;
	db->bot.bot_size += (calc_codage_and_instruction_size(db) + 2);
}

void		handle_sti_instruction(t_db *db, const char *inst)
{
	allocate_new_instruction(db);
	db->bot.instructions[db->inst_counter - 1].type = e_sti;
	db->bot.instructions[db->inst_counter - 1].arguments_count = 3;
	inst = skip_whitespaces(inst);
	inst += handle_register_argument(db, inst, 1);
	inst = skip_whitespaces(inst);
	if (*inst != ',')
		clean_and_exit(db, "THERE IS NO 2nd ARGUMENT IN STI INSTRUCTION");
	++inst;
	inst = skip_whitespaces(inst);
	if (*inst != 'r' && *inst != '-' && *inst != ':'
		&& !ft_isdigit(*inst) && *inst != '%')
		clean_and_exit(db, "WRONG 2nd ARGUMENT IN STI INSTRUCTION");
	if (*inst == 'r')
		inst += handle_register_argument(db, inst, 2);
	else if (*inst == '%')
		inst += (handle_direct_argument(db, inst + 1, 2) + 1);
	else
		inst += handle_indirect_argument(db, inst, 2);
	while (ft_isdigit(*inst))
		++inst;
	inst = skip_whitespaces(inst);
	sti_extended(db, inst);
}
