/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dsp_zjmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 14:55:22 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/26 11:51:37 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void	print_zjmp(t_carriage *carriage, t_args *args)
{
	ft_printf("P%5d | zjmp %d ", carriage->num_car, args->arg1.value);
	if (carriage->carry)
		ft_putstr("OK\n");
	else
		ft_putstr("FAILED\n");
}

int		dsp_zjmp(t_carriage *carriage, unsigned char *map, t_args *args, int *shift)
{
	int			res;

	res = 0;
	ft_memset(args, 0, sizeof(t_args));
	read_short_from_map(&args->arg1.value, carriage->pc + 1, map);
	args->arg1.readed = args->arg1.value;
	args->arg1.type = T_DIR;
	args->arg1.size = 2;
	if (carriage->carry)
	{
		*shift = args->arg1.value % IDX_MOD;
		res = 1;
	}
	else
		*shift = args->arg1.size;
	return (res);
}
