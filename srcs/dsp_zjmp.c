/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dsp_zjmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 14:55:22 by oevtushe          #+#    #+#             */
/*   Updated: 2018/09/22 19:32:41 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void	print_zjmp(t_carriage *carriage, t_vm *vm)
{
	print_pnum(carriage->num_car);
	printf("zjmp %d ", vm->args.arg1.value);
	if (carriage->carry)
		printf("OK\n");
	else
		printf("FAILED\n");
}

/*
** name: zjmp
** opcode: 9
** cycles: 20
** ACB: no
**
** Description:
** 	Take an index and jump to this address if the carry is 1
*/

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
