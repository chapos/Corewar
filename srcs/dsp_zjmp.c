/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dsp_zjmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 14:55:22 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/24 14:47:39 by oevtushe         ###   ########.fr       */
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

int		dsp_zjmp(t_carriage *carriage, unsigned char *map, t_visual *visual, int *shift)
{
	int			res;
	t_args		args;

	res = 0;
	visual->op = map[carriage->pc];
	ft_memset(&visual->args, 0, sizeof(t_args));
	read_short_from_map(&args.arg1.value, carriage->pc + 1, map);
	args.arg1.readed = args.arg1.value;
	args.arg1.type = T_DIR;
	args.arg1.size = 2;
	visual->args = args;
	*shift = carriage->carry ? args.arg1.value % IDX_MOD : args.arg1.size;
	res = 1;
	return (res);
}
