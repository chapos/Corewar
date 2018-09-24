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

void			set_labels_to_instructions(t_db *db)
{
	size_t i;
	size_t j;

	i = 0;
	while (i < db->inst_counter)
	{
		j = 0;
		while (j < db->bot.instructions[i].arguments_count)
		{
			if (db->bot.instructions[i].args[j].lable)
			{
				if (db->bot.instructions[i].args[j].type == e_undirect)
					db->bot.instructions[i].args[j].value =
				big_little_endian(calculate_label_position(db, i, j), false);
				else
					db->bot.instructions[i].args[j].value =
					big_little_endian(calculate_label_position(db, i, j),
					get_direct_arg_size_by_name(db->bot.instructions[i].type)
					== 4 ? true : false);
			}
			++j;
		}
		++i;
	}
}

size_t			calc_codage_and_instruction_size(t_db *db)
{
	t_argument	a_t;
	size_t		i;
	uint32_t	bot_size;

	bot_size = 0;
	i = 0;
	while (i < db->bot.instructions[db->inst_counter - 1].arguments_count)
	{
		a_t = db->bot.instructions[db->inst_counter - 1].args[i].type;
		db->bot.instructions[db->inst_counter - 1].codage |= a_t;
		db->bot.instructions[db->inst_counter - 1].codage <<= 2;
		if (db->bot.instructions[db->inst_counter - 1].args[i].type == e_direct)
			bot_size += get_direct_arg_size_by_name(db->bot.instructions
					[db->inst_counter - 1].type);
		else if (db->bot.instructions[db->inst_counter - 1].args[i].type
			== e_register)
			bot_size += 1;
		else
			bot_size += 2;
		++i;
	}
	db->bot.instructions[db->inst_counter - 1].codage <<= 8 - ((i + 1) * 2);
	return (bot_size);
}

t_instruction	get_instruction(const char *line)
{
	t_instruction instruction;

	if (ft_strnequ(line, "live", 4) || ft_strnequ(line, "aff", 3))
		instruction = ft_strnequ(line, "live", 4) ? e_live : e_aff;
	else if (ft_strnequ(line, "sti", 3) || ft_strnequ(line, "add", 3))
		instruction = ft_strnequ(line, "sti", 3) ? e_sti : e_add;
	else if (ft_strnequ(line, "sub", 3) || ft_strnequ(line, "and", 3))
		instruction = ft_strnequ(line, "sub", 3) ? e_sub : e_and;
	else if (ft_strnequ(line, "or", 2) || ft_strnequ(line, "xor", 3))
		instruction = ft_strnequ(line, "or", 2) ? e_or : e_xor;
	else if (ft_strnequ(line, "zjmp", 4) || ft_strnequ(line, "ldi", 3))
		instruction = ft_strnequ(line, "zjmp", 4) ? e_zjmp : e_ldi;
	else if (ft_strnequ(line, "st", 2) || ft_strnequ(line, "fork", 4))
		instruction = ft_strnequ(line, "st", 2) ? e_st : e_fork;
	else if (ft_strnequ(line, "lld", 3) || ft_strnequ(line, "lldi", 4))
		instruction = ft_strnequ(line, "lldi", 4) ? e_lldi : e_lld;
	else if (ft_strnequ(line, "lfork", 5) || ft_strnequ(line, "ld", 2))
		instruction = ft_strnequ(line, "lfork", 5) ? e_lfork : e_ld;
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
	db->bot.instructions[db->inst_counter - 1].instruction_size = 5;
	db->bot.bot_size += 5;
}

void			handle_ld_lld_instruction(t_db *db, const char *inst,
		t_instruction type)
{
	while (ft_iswhitespace(*inst))
		++inst;
	if (*inst != '%' && *inst != '-'
		&& *inst != ':' && !ft_isdigit(*inst))
		clean_and_exit(db, "WRONG 1st ARGUMENT IN LD/LLD INSTRUCTION");
	allocate_new_instruction(db);
	db->bot.instructions[db->inst_counter - 1].type = type;
	db->bot.instructions[db->inst_counter - 1].arguments_count = 2;
	inst += *inst == '%' ? handle_direct_argument(db, ++inst, 1) :
			handle_indirect_argument(db, inst, 1);
	while (ft_isdigit(*inst))
		++inst;
	while (ft_iswhitespace(*inst))
		++inst;
	if (*inst != ',')
		clean_and_exit(db, "THERE IS NO 2nd ARGUMENT IN LD/LLD INSTRUCTION");
	inst += (handle_register_argument(db, inst + 1, 2) + 1);
	while (ft_iswhitespace(*inst))
		++inst;
	if (*inst != '\0' && *inst != ';' && *inst != '#')
		clean_and_exit(db, "LD/LLD INSTRUCTION SYNTAX ERROR");
	db->bot.instructions[db->inst_counter - 1].instruction_size =
			calc_codage_and_instruction_size(db) + 2;
	db->bot.bot_size += (calc_codage_and_instruction_size(db) + 2);
}
