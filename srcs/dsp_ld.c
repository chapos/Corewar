/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dsp_ld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 14:36:19 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/20 11:51:44 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

/*
** Modifies carry
** Has ACB
*/

int		dsp_ld(t_carriage *carriage, unsigned char *map)
{
	unsigned char	acb;
	t_args			args;
	int				res;

	res = 0;
	acb = map[(carriage->pc + 1) % MEM_SIZE];
	ft_memset(&args, 0, sizeof(t_args));
	if ((acb & ARG_MASK1) || (acb & ARG_MASK2))
	{
		read_args_from_map(carriage->pc, map, &args, (t_reader){read_int_from_map, read_short_from_map});
		if (CHECK_REG(args.arg2.type, args.arg2.readed) && (args.arg1.type == T_DIR ||
					args.arg1.type == T_IND))
		{
			init_args(carriage, map, &args);
			carriage->reg[args.arg2.readed] = args.arg1.value;
			carriage->carry = args.arg1.value == 0 ? 1 : 0;
			res = 1;
		}
		carriage->pc += args.arg1.size + args.arg2.size + 1;
	}
	++carriage->pc;
	carriage->pc %= MEM_SIZE;
	return (res);
}
