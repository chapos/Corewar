/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dsp_st.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 14:37:28 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/27 14:50:01 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void	print_st(t_carriage *carriage, t_args *args)
{
	print_pnum(carriage->num_car);
	ft_putstr("st");
	if (args->arg2.type == T_IND)
		ft_printf(" r%d %d\n", (unsigned char)args->arg1.readed, args->arg2.value);
	else
		ft_printf(" r%d %hhu\n", (unsigned char)args->arg1.readed, (unsigned char)args->arg2.readed);
	carriage = NULL;
}

int		dsp_st(t_carriage *carriage, unsigned char *map, t_args *args, int *shift)
{
	unsigned char	acb;
	int				res;
	int				rev;
	int				tmp;

	tmp = 0;
	res = 0;
	acb = map[(carriage->pc + 1) % MEM_SIZE];
	ft_memset(args, 0, sizeof(t_args));
	*shift = 1;
	// '||' because of ACB Invalid cases
	if ((acb & ARG_MASK1) || (acb & ARG_MASK2))
	{
		read_args_from_map(carriage->pc, map, args, (t_reader){read_int_from_map, read_short_from_map});
		if (args->arg2.type == T_IND)
		{
			tmp = args->arg2.readed;
			args->arg2.readed %= IDX_MOD;
		}
		if (CHECK_REG(args->arg1.type, args->arg1.readed) && (args->arg2.type == T_IND ||
				args->arg2.type == T_REG))
		{
			init_args(carriage, map, args);
			if (args->arg2.type == T_REG)
			{
				carriage->reg[args->arg2.readed] = args->arg1.value;
				res = 1;
			}
			else
			{
				rev = args->arg1.value;
				ft_byterev_ui32((unsigned int *)&rev);
				write_int_in_map(&rev, carriage->pc + args->arg2.readed, map);
				res = 1;
			}
		}
		*shift += args->arg1.size + args->arg2.size;
		args->arg2.value = tmp;
	}
	return (res);
}
