/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dsp_and.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 14:39:30 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/24 10:46:34 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void	print_and(t_carriage *carriage, t_visual *visual)
{
	ft_printf("%s", visual->op_names[visual->op - 1]);
	if (visual->args.arg1.type == T_REG)
		ft_printf(" r%hhu", visual->args.arg1.readed);
	else
		ft_printf(" %d", visual->args.arg1.value);
	if (visual->args.arg2.type == T_REG)
		ft_printf(" r%hhu", visual->args.arg2.readed);
	else
		ft_printf(" %d", visual->args.arg2.value);
	ft_printf(" r%hhu\n", visual->args.arg3.readed);
	carriage = NULL;
}

int		dsp_and(t_carriage *carriage, unsigned char *map, t_visual *visual, int *shift)
{
	unsigned char	acb;
	int				res;
	t_args			args;
	unsigned int	and;

	res = 0;
	visual->op = map[carriage->pc];
	acb = map[(carriage->pc + 1) % MEM_SIZE];
	ft_memset(&args, 0, sizeof(t_args));
	if ((acb & ARG_MASK1) || (acb & ARG_MASK2) || (acb & ARG_MASK3))
	{
		read_args_from_map(carriage->pc, map, &args, (t_reader){read_int_from_map, read_short_from_map});
		if (args.arg1.type == T_IND)
			args.arg1.readed %= IDX_MOD;
		if (args.arg2.type == T_IND)
			args.arg2.readed %= IDX_MOD;
		if ((acb & ARG_MASK1) && (acb & ARG_MASK2) && CHECK_REG(args.arg3.type, args.arg3.readed))
		{
			init_args(carriage, map, &args);
			and = args.arg1.value & args.arg2.value;
			carriage->reg[args.arg3.readed] = and;
			carriage->carry = and ? 0 : 1;
			res = 1;
		}
		*shift = 1 + args.arg1.size + args.arg2.size + args.arg3.size;
		visual->args = args;
	}
	return (res);
}
