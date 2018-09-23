/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_validation_ext3.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <eyevresh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 11:54:00 by eyevresh          #+#    #+#             */
/*   Updated: 2018/09/23 11:54:00 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

void	validate_and_save_instruction_ext(t_db *db, char *instruction)
{
	if (get_instruction(instruction) == e_and)
		handle_and_or_xor_instruction(db, instruction + 3, e_and);
	else if (get_instruction(instruction) == e_or)
		handle_and_or_xor_instruction(db, instruction + 2, e_or);
	else if (get_instruction(instruction) == e_xor)
		handle_and_or_xor_instruction(db, instruction + 3, e_xor);
	else if (get_instruction(instruction) == e_zjmp)
		handle_zjmp_instruction(db, instruction + 4);
	else if (get_instruction(instruction) == e_lld)
		handle_ld_lld_instruction(db, instruction + 3, e_lld);
	else if (get_instruction(instruction) == e_sti)
		handle_sti_instruction(db, instruction + 3);
	else if (get_instruction(instruction) == e_fork)
		handle_fork_lfork_instruction(db, instruction + 4, e_fork);
	else if (get_instruction(instruction) == e_lfork)
		handle_fork_lfork_instruction(db, instruction + 5, e_lfork);
	else
		handle_aff_instruction(db, instruction + 3);
}

void	handle_fork_lfork_instruction(t_db *db, const char *inst,
										t_instruction type)
{
	allocate_new_instruction(db);
	db->bot.instructions[db->inst_counter - 1].type = type;
	db->bot.instructions[db->inst_counter - 1].arguments_count = 1;
	inst = skip_whitespaces(inst);
	if (*inst != '%')
		clean_and_exit(db, "WRONG 1st ARGUMENT IN FORK/LFORK INSTRUCTION");
	++inst;
	inst += handle_direct_argument(db, inst, 1);
	while (ft_isdigit(*inst))
		++inst;
	inst = skip_whitespaces(inst);
	if (*inst != '\0' && *inst != ';' && *inst != '#')
		clean_and_exit(db, "FORK/LFORK INSTRUCTION SYNTAX ERROR");
	db->bot.instructions[db->inst_counter - 1].instruction_size = 3;
	db->bot.bot_size += 3;
}

void	handle_aff_instruction(t_db *db, const char *inst)
{
	allocate_new_instruction(db);
	db->bot.instructions[db->inst_counter - 1].type = e_aff;
	db->bot.instructions[db->inst_counter - 1].arguments_count = 1;
	inst = skip_whitespaces(inst);
	inst += handle_register_argument(db, inst, 1);
	inst = skip_whitespaces(inst);
	if (*inst != '\0' && *inst != ';' && *inst != '#')
		clean_and_exit(db, "AFF INSTRUCTION SYNTAX ERROR");
	db->bot.instructions[db->inst_counter - 1].instruction_size =
			calc_codage_and_instruction_size(db) + 2;
	db->bot.bot_size += (calc_codage_and_instruction_size(db) + 2);
}
