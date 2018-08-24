/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dsp_aff.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 14:17:04 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/23 16:30:54 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void	print_aff(t_carriage *carriage, t_visual *visual)
{
	carriage = NULL;
	visual = NULL;
}

int		dsp_aff(t_carriage *carriage, unsigned char *map, t_visual *visual, int *shift)
{
	unsigned char	acb;
	int				res;
	t_args			args;

	res = 0;
	visual->op = map[carriage->pc];
	acb = map[(carriage->pc + 1) % MEM_SIZE];
	ft_memset(&args, 0, sizeof(t_args));
	if ((acb & ARG_MASK1))
	{
		read_args_from_map(carriage->pc, map, &args, (t_reader){read_int_from_map, read_short_from_map});
		if (CHECK_REG(args.arg1.type, args.arg1.readed))
		{
			ft_putchar((char)carriage->reg[args.arg1.readed]);
			res = 1;
		}
		*shift = 1 + args.arg1.size;
		visual->args = args;
	}
	return (res);
}
