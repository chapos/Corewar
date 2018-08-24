/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dsp_sub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 14:38:57 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/24 10:53:17 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void	print_sub(t_carriage *carriage, t_visual *visual)
{
	ft_printf("%s r%hhu r%hhu r%hhu\n", visual->op_names[visual->op - 1],
			(unsigned char)visual->args.arg1.readed, (unsigned char)visual->args.arg2.readed, (unsigned char)visual->args.arg3.readed);
	carriage = NULL;
}

int		dsp_sub(t_carriage *carriage, unsigned char *map, t_visual *visual, int *shift)
{
	unsigned char	acb;
	int				res;
	t_args			args;
	unsigned int	sub;

	res = 0;
	visual->op = map[carriage->pc];
	acb = map[(carriage->pc + 1) % MEM_SIZE];
	ft_memset(&args, 0, sizeof(t_args));
	if ((acb & ARG_MASK1) || (acb & ARG_MASK2) || (acb & ARG_MASK3))
	{
		read_args_from_map(carriage->pc, map, &args, (t_reader){read_int_from_map, read_short_from_map});
		if (CHECK_REG(args.arg1.type, args.arg1.readed) && CHECK_REG(args.arg2.type, args.arg2.readed) &&
				CHECK_REG(args.arg3.type, args.arg3.readed))
		{
			sub = carriage->reg[args.arg1.readed] - carriage->reg[args.arg2.readed];
			carriage->reg[args.arg3.readed] = sub;
			carriage->carry = sub ? 0 : 1;
			res = 1;
		}
		visual->args = args;
		*shift = 1 + args.arg1.size + args.arg2.size + args.arg3.size;
	}
	return (res);
}
