/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic_handling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <eyevresh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 16:41:00 by eyevresh          #+#    #+#             */
/*   Updated: 2018/09/23 16:41:00 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

void			jesus_save_me(t_db *db, const char *inst, int a_n)
{
	if (*inst != ':' && *inst != '-' && !ft_isdigit(*inst))
		clean_and_exit(db, "DIRECT ARGUMENT SYNTAX ERROR IN INSTRUCTION");
	if (*inst == '-' && !ft_isdigit(*(inst + 1)))
		clean_and_exit(db, "DIRECT ARGUMENT SYNTAX ERROR IN INSTRUCTION");
	db->bot.instructions[db->inst_counter - 1].args[a_n - 1].type = e_direct;
	db->bot.instructions[db->inst_counter - 1].args[a_n - 1].end_mark =
		get_direct_arg_size_by_name(db->bot.instructions[db->inst_counter - 1]
												.type) == 4 ? true : false;
}

static uint32_t	perform_op(uint32_t left, int right, char op, bool mark)
{
	uint32_t res;

	left = big_little_endian(left, mark);
	if (op == '-')
		res = (int)left - right;
	else if (op == '+')
		res = (int)left + right;
	else if (op == '*')
		res = (int)left * right;
	else if (op == '/')
	{
		if (right == 0)
			return (big_little_endian(left, mark));
		res = left / right;
	}
	else
	{
		if (right == 0)
			return (big_little_endian(left, mark));
		res = left % right;
	}
	return (big_little_endian(res, mark));
}

void			do_calculation(t_db *db)
{
	size_t i;
	size_t j;

	i = 0;
	while (i < db->inst_counter)
	{
		j = 0;
		while (j < db->bot.instructions[i].arguments_count)
		{
			if (db->bot.instructions[i].args[j].expr.op != '\0')
				db->bot.instructions[i].args[j].value = perform_op(
						db->bot.instructions[i].args[j].value,
						db->bot.instructions[i].args[j].expr.value,
						db->bot.instructions[i].args[j].expr.op,
						db->bot.instructions[i].args[j].end_mark);
			++j;
		}
		++i;
	}
}

size_t			handle_expression(t_db *db, const char *inst, size_t l, int a)
{
	size_t tmp;

	tmp = l;
	db->bot.instructions[db->inst_counter - 1].args[a - 1].expr.op = '\0';
	db->bot.instructions[db->inst_counter - 1].args[a - 1].expr.value = 0;
	while (ft_isdigit(inst[l]))
		++l;
	while (ft_iswhitespace(inst[l]))
		++l;
	if (inst[l] != '+' && inst[l] != '-' && inst[l] != '*' && inst[l] != '/'
		&& inst[l] != '%')
		return (0);
	db->bot.instructions[db->inst_counter - 1].args[a - 1].expr.op = inst[l++];
	while (ft_iswhitespace(inst[l]))
		++l;
	if (inst[l] == '\0')
		return (0);
	if (!ft_isdigit(inst[l]) && !(inst[l] == '-' && ft_isdigit(inst[l + 1])))
		return (0);
	db->bot.instructions[db->inst_counter - 1].args[a - 1].expr.value =
			ft_atoi(inst + l);
	l += inst[l] == '-' ? 1 : 0;
	while (ft_isdigit(inst[l]))
		++l;
	return (l - tmp);
}
