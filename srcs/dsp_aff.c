/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dsp_aff.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 14:17:04 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/25 15:38:01 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void	print_aff(t_carriage *carriage, t_args *args)
{
	carriage = NULL;
	args = NULL;
}

int		dsp_aff(t_carriage *carriage, unsigned char *map, t_args *args, int *shift)
{
	unsigned char	acb;
	int				res;

	res = 0;
	acb = map[(carriage->pc + 1) % MEM_SIZE];
	ft_memset(args, 0, sizeof(t_args));
	*shift = 1;
	if ((acb & ARG_MASK1))
	{
		read_args_from_map(carriage->pc, map, args, (t_reader){read_int_from_map, read_short_from_map});
		if (CHECK_REG(args->arg1.type, args->arg1.readed))
		{
			ft_putchar((char)carriage->reg[args->arg1.readed]);
			res = 1;
		}
		*shift += args->arg1.size;
	}
	return (res);
}
