/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dsp_zjmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 14:55:22 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/30 15:24:37 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void	print_zjmp(t_carriage *carriage, t_vm *vm)
{
	print_pnum(carriage->num_car);
	ft_printf("zjmp %d ", vm->args.arg1.value);
	if (carriage->carry)
		ft_putstr("OK\n");
	else
		ft_putstr("FAILED\n");
}

int		dsp_zjmp(t_carriage *carriage, t_vm *vm)
{
	int			res;

	res = 0;
	ft_memset(&vm->args, 0, sizeof(t_args));
	read_short_from_map(&vm->args.arg1.value, carriage->pc + 1, vm->map);
	vm->args.arg1.readed = vm->args.arg1.value;
	vm->args.arg1.type = T_DIR;
	vm->args.arg1.size = 2;
	if (carriage->carry)
	{
		vm->args.shift = vm->args.arg1.value % IDX_MOD;
		res = 1;
	}
	else
		vm->args.shift = vm->args.arg1.size;
	return (res);
}
