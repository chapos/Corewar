/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dsp_sti.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 12:46:11 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/27 14:50:18 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void	print_sti(t_carriage *carriage, t_args *args)
{
	int		sum;
	int		rf;

	sum = (args->arg2.value + args->arg3.value) % IDX_MOD;
	rf = (carriage->pc + sum) % MEM_SIZE;
	print_pnum(carriage->num_car);
	ft_printf("sti r%hhu %d %d\n", (unsigned char)args->arg1.readed, args->arg2.value, args->arg3.value);
	ft_printf("%6.0d | -> store to %d + %d = %d (with pc and mod %d)\n", 0,
			args->arg2.value, args->arg3.value,
			args->arg2.value + args->arg3.value, rf);
}

int		dsp_sti(t_carriage *carriage, unsigned char *map, t_args *args, int *shift)
{
	unsigned char	acb;
	int				res;
	int				addr;
	int				rev;

	res = 0;
	acb = map[(carriage->pc + 1) % MEM_SIZE];
	ft_memset(args, 0, sizeof(t_args));
	*shift = 1;
	if ((acb & ARG_MASK1) || (acb & ARG_MASK2) || (acb & ARG_MASK3))
	{
		read_args_from_map(carriage->pc, map, args, (t_reader){read_short_from_map, read_short_from_map});
		if (args->arg2.type == T_IND)
			args->arg2.readed %= IDX_MOD;
		if (CHECK_REG(args->arg1.type, args->arg1.readed) && (acb & ARG_MASK2) &&
				(args->arg3.type == T_DIR || CHECK_REG(args->arg3.type, args->arg3.readed)))
		{
			init_args(carriage, map, args);
			addr = (args->arg2.value + args->arg3.value) % IDX_MOD;
			rev = args->arg1.value;
			ft_byterev_ui32((unsigned int *)&rev);
			write_int_in_map(&rev, carriage->pc + addr, map);
			res = 1;
		}
		*shift += args->arg1.size + args->arg2.size + args->arg3.size;
	}
	return (res);
}
