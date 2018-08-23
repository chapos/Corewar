/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dsp_lldi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 12:53:52 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/23 15:51:37 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void	print_lldi(t_carriage *carriage, t_visual *visual)
{
	ft_printf("%s %d %d r%hhu\n", visual->op_names[visual->op - 1], visual->args.arg1.value, visual->args.arg2.value, (unsigned char)visual->args.arg3.readed);
	ft_printf("-> load from %d + %d = %d (with pc and mod %d)\n",
			visual->args.arg1.value, visual->args.arg2.value,
			visual->args.arg1.value + visual->args.arg2.value,
			carriage->pc);
}

int		dsp_lldi(t_carriage *carriage, unsigned char *map, t_visual *visual)
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
		if ((acb & ARG_MASK1) && (args.arg2.type == T_DIR ||
					CHECK_REG(args.arg2.type, args.arg2.readed)) && CHECK_REG(args.arg3.type, args.arg3.readed))
		{
			init_args(carriage, map, &args);
			val = args.arg1.value + args.arg2.value;
			carriage->carry = val ? 0 : 1;
			read_int_from_map(&val, carriage->pc + val, map);
			carriage->reg[args.arg3.readed] = val;
			res = 1;
		}
		carriage->pc += 1 + args.arg1.size + args.arg2.size + args.arg3.size;
		visual->args = args;
	}
	++carriage->pc;
	carriage->pc %= MEM_SIZE;
	return (res);
}
