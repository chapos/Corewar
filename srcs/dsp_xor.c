/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dsp_xor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 14:41:56 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/25 18:25:50 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void	print_xor(t_carriage *carriage, t_args *args)
{
	ft_printf("P%5d | xor", carriage->num_car);
	if (args->arg1.type == T_REG)
		ft_printf(" r%hhu", args->arg1.readed);
	else
		ft_printf(" %d", args->arg1.value);
	if (args->arg2.type == T_REG)
		ft_printf(" r%hhu", args->arg2.readed);
	else
		ft_printf(" %d", args->arg2.value);
	ft_printf(" r%hhu\n", args->arg3.readed);
	carriage = NULL;
}

int		dsp_xor(t_carriage *carriage, unsigned char *map, t_args *args, int *shift)
{
	unsigned char	acb;
	int				res;
	unsigned int	xor;

	res = 0;
	acb = map[(carriage->pc + 1) % MEM_SIZE];
	ft_memset(args, 0, sizeof(t_args));
	*shift = 1;
	if ((acb & ARG_MASK1) || (acb & ARG_MASK2) || (acb & ARG_MASK3))
	{
		read_args_from_map(carriage->pc, map, args, (t_reader){read_int_from_map, read_short_from_map});
		if (args->arg1.type == T_IND)
			args->arg1.readed %= IDX_MOD;
		if (args->arg2.type == T_IND)
			args->arg2.readed %= IDX_MOD;
		if ((acb & ARG_MASK1) && (acb & ARG_MASK2) && CHECK_REG(args->arg3.type, args->arg3.readed))
		{
			init_args(carriage, map, args);
			xor = args->arg1.value ^ args->arg2.value;
			carriage->reg[args->arg3.readed] = xor;
			carriage->carry = xor ? 0 : 1;
			res = 1;
		}
		*shift += args->arg1.size + args->arg2.size + args->arg3.size;
	}
	return (res);
}
