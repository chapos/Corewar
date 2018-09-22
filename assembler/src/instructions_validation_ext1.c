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

void			handle_st_instruction(t_db *db, const char *inst)
{
	inst += 2;
	allocate_new_instruction(db);
	db->bot.instructions[db->inst_counter - 1].type = e_st;
	db->bot.instructions[db->inst_counter - 1].arguments_count = 2;
	while (ft_iswhitespace(*inst))
		++inst;
	inst += handle_register_argument(db, inst, 1);
	while (ft_iswhitespace(*inst))
		++inst;
	if (*inst != ',')
		clean_and_exit(db, "THERE IS NO 2nd ARGUMENT IN ST INSTRUCTION");
	++inst;
	while (ft_iswhitespace(*inst))
		++inst;
	if (*inst != 'r' && *inst != '-'
		&& *inst != ':' && !ft_isdigit(*inst))
		clean_and_exit(db, "WRONG 2nd ARGUMENT IN ST INSTRUCTION");
	inst += *inst == 'r' ? handle_register_argument(db, inst, 2)
			: handle_indirect_argument(db, inst, 2);
	while (ft_isdigit(*inst))
		++inst;
	while (ft_iswhitespace(*inst))
		++inst;
	if (*inst != '\0' && *inst != ';' && *inst != '#')
		clean_and_exit(db, "ST INSTRUCTION SYNTAX ERROR");
	db->bot.instructions[db->inst_counter - 1].instruction_size =
			calc_codage_and_instruction_size(db) + 2;
	db->bot.bot_size += (calc_codage_and_instruction_size(db) + 2);
	//TODO::test st instruction
	//TODO::retest ld instruction with register argument
	//TODO::fix norms
}
