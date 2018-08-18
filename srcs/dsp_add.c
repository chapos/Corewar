/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dsp_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 14:38:11 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/18 14:38:18 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

int		dsp_add(t_carriage *carriage, unsigned char *map)
{
	unsigned char	acb;
	int				res;
	t_args			args;
	unsigned int	sum;

	res = 0;
	acb = map[carriage->pc + 1];
	ft_memset(&args, 0, sizeof(t_args));
	if ((acb & ARG_MASK1) || (acb & ARG_MASK2) || (acb & ARG_MASK3))
	{
		read_args_from_map(carriage->pc, map, &args);
		if (CHECK_REG(args.arg1.type, args.arg1.readed) && CHECK_REG(args.arg2.type, args.arg2.readed) &&
				CHECK_REG(args.arg3.type, args.arg3.readed))
		{
			sum = carriage->reg[args.arg1.readed] + carriage->reg[args.arg2.readed];
			carriage->reg[args.arg3.readed] = sum;
			carriage->carry = sum ? 0 : 1;
			res = 1;
		}
		carriage->pc += 1 + args.arg1.size + args.arg2.size + args.arg3.size;
	}
	++carriage->pc;
	carriage->pc %= MEM_SIZE;
	return (res);
}
