/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dsp_ldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 12:11:31 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/24 16:49:21 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void	print_ldi(t_carriage *carriage, t_visual *visual)
{
	int		sum;
	int		rf;

	sum = (visual->args.arg1.value + visual->args.arg2.value) % IDX_MOD;
	rf = carriage->pc + sum;
	rf %= MEM_SIZE;
	if (rf < 0)
		rf = MEM_SIZE + rf;
	ft_printf("%s %d %d r%hhu\n", visual->op_names[visual->op - 1], visual->args.arg1.value, visual->args.arg2.value, (unsigned char)visual->args.arg3.readed);
	ft_printf("-> load from %d + %d = %d (with pc and mod %d)\n",
			visual->args.arg1.value, visual->args.arg2.value,
			visual->args.arg1.value + visual->args.arg2.value, rf);
}

int		dsp_ldi(t_carriage *carriage, unsigned char *map, t_visual *visual, int *shift)
{
	unsigned char	acb;
	int				res;
	t_args			args;
	int				val;

	res = 0;
	visual->op = map[carriage->pc];
	acb = map[(carriage->pc + 1) % MEM_SIZE];
	ft_memset(&args, 0, sizeof(t_args));
	if ((acb & ARG_MASK1) || (acb & ARG_MASK2) || (acb & ARG_MASK3))
	{
		read_args_from_map(carriage->pc, map, &args, (t_reader){read_short_from_map, read_short_from_map});
		if (args.arg1.type == T_IND)
			args.arg1.readed %= IDX_MOD;
		if ((acb & ARG_MASK1) && (args.arg2.type == T_DIR ||
					CHECK_REG(args.arg2.type, args.arg2.readed)) && CHECK_REG(args.arg3.type, args.arg3.readed))
		{
			init_args(carriage, map, &args);
			val = (args.arg1.value + args.arg2.value) % IDX_MOD;
			read_int_from_map(&val, carriage->pc + val, map);
			carriage->reg[args.arg3.readed] = val;
			res = 1;
		}
		visual->args = args;
		*shift = 1 + args.arg1.size + args.arg2.size + args.arg3.size;
	}
	return (res);
}
