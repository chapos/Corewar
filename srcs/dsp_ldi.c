/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dsp_ldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 12:11:31 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/27 14:47:24 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void	print_ldi(t_carriage *carriage, t_args *args)
{
	int		sum;
	int		rf;

	sum = (args->arg1.value + args->arg2.value) % IDX_MOD;
	rf = (carriage->pc + sum) % MEM_SIZE;
	print_pnum(carriage->num_car);
	ft_printf("ldi %d %d r%hhu\n", args->arg1.value,
			args->arg2.value, (unsigned char)args->arg3.readed);
	ft_printf("%6.0d | -> load from %d + %d = %d (with pc and mod %d)\n", 0,
			args->arg1.value, args->arg2.value,
			args->arg1.value + args->arg2.value, rf);
}

int		dsp_ldi(t_carriage *carriage, unsigned char *map, t_args *args, int *shift)
{
	unsigned char	acb;
	int				res;
	int				val;

	res = 0;
	acb = map[(carriage->pc + 1) % MEM_SIZE];
	ft_memset(args, 0, sizeof(t_args));
	*shift = 1;
	if ((acb & ARG_MASK1) || (acb & ARG_MASK2) || (acb & ARG_MASK3))
	{
		read_args_from_map(carriage->pc, map, args, (t_reader){read_short_from_map, read_short_from_map});
		if (args->arg1.type == T_IND)
			args->arg1.readed %= IDX_MOD;
		if ((acb & ARG_MASK1) && (args->arg2.type == T_DIR ||
					CHECK_REG(args->arg2.type, args->arg2.readed)) && CHECK_REG(args->arg3.type, args->arg3.readed))
		{
			init_args(carriage, map, args);
			val = (args->arg1.value + args->arg2.value) % IDX_MOD;
			read_int_from_map(&val, carriage->pc + val, map);
			carriage->reg[args->arg3.readed] = val;
			res = 1;
		}
		*shift += args->arg1.size + args->arg2.size + args->arg3.size;
	}
	return (res);
}
