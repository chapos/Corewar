/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dsp_zjmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 14:55:22 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/23 15:37:02 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void	print_zjmp(t_carriage *carriage, t_visual *visual)
{
	ft_printf("%s %d ", visual->op_names[visual->op - 1], visual->args.arg1.value);
	if (carriage->carry)
		ft_putstr("OK\n");
	else
		ft_putstr("FAILED\n");
}

int		dsp_zjmp(t_carriage *carriage, unsigned char *map, t_visual *visual)
{
	int			res;
	t_args		args;

	res = 0;
	visual->op = map[carriage->pc];
	ft_memset(&visual->args, 0, sizeof(t_args));
	read_short_from_map(&args.arg1.value, carriage->pc + 1, map);
	args.arg1.readed = args.arg1.value;
	args.arg1.type = T_DIR;
	visual->args = args;
	if (carriage->carry)
	{
		carriage->pc += args.arg1.value; // val % IDX_MOD;
		res = 1;
	}
	++carriage->pc;
	carriage->pc %= MEM_SIZE;
	if (carriage->pc < 0)
		carriage->pc = MEM_SIZE + carriage->pc;
	return (res);
}
