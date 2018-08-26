/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dsp_sub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 14:38:57 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/25 18:25:24 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void	print_sub(t_carriage *carriage, t_args *args)
{
	ft_printf("P%5d | sub r%hhu r%hhu r%hhu\n", carriage->num_car, (unsigned char)args->arg1.readed,
			(unsigned char)args->arg2.readed, (unsigned char)args->arg3.readed);
	carriage = NULL;
}

int		dsp_sub(t_carriage *carriage, unsigned char *map, t_args *args, int *shift)
{
	unsigned char	acb;
	int				res;
	unsigned int	sub;

	res = 0;
	acb = map[(carriage->pc + 1) % MEM_SIZE];
	ft_memset(args, 0, sizeof(t_args));
	*shift = 1;
	if ((acb & ARG_MASK1) || (acb & ARG_MASK2) || (acb & ARG_MASK3))
	{
		read_args_from_map(carriage->pc, map, args, (t_reader){read_int_from_map, read_short_from_map});
		if (CHECK_REG(args->arg1.type, args->arg1.readed) && CHECK_REG(args->arg2.type, args->arg2.readed) &&
				CHECK_REG(args->arg3.type, args->arg3.readed))
		{
			sub = carriage->reg[args->arg1.readed] - carriage->reg[args->arg2.readed];
			carriage->reg[args->arg3.readed] = sub;
			carriage->carry = sub ? 0 : 1;
			res = 1;
		}
		*shift += args->arg1.size + args->arg2.size + args->arg3.size;
	}
	return (res);
}
