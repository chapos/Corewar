/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dsp_sti.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 12:46:11 by oevtushe          #+#    #+#             */
/*   Updated: 2018/09/01 12:34:31 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void	print_sti(t_carriage *carriage, t_vm *vm)
{
	int		sum;
	int		rf;

	sum = (vm->args.arg2.value + vm->args.arg3.value) % IDX_MOD;
	rf = carriage->pc + sum;
	print_pnum(carriage->num_car);
	printf("sti r%hhu %d %d\n", (unsigned char)vm->args.arg1.readed, vm->args.arg2.value, vm->args.arg3.value);
	printf("%6.0d | -> store to %d + %d = %d (with pc and mod %d)\n", 0,
			  vm->args.arg2.value, vm->args.arg3.value,
			  vm->args.arg2.value + vm->args.arg3.value, rf);
}

int		dsp_sti(t_carriage *carriage, t_vm *vm)
{
	unsigned char	acb;
	int				res;
	int				addr;
	int				rev;

	res = 0;
	acb = vm->map[(carriage->pc + 1) % MEM_SIZE];
	ft_memset(&vm->args, 0, sizeof(t_args));
	vm->args.shift = 1;
	if ((acb & ARG_MASK1) || (acb & ARG_MASK2) || (acb & ARG_MASK3))
	{
		read_args_from_map(carriage->pc, vm->map, &vm->args, (t_reader){read_short_from_map, read_short_from_map});
		if (vm->args.arg2.type == T_IND)
			vm->args.arg2.readed %= IDX_MOD;
		if (CHECK_REG(vm->args.arg1.type, vm->args.arg1.readed) && CH_ALL(vm->args.arg2.type, vm->args.arg2.readed) &&
				(vm->args.arg3.type == T_DIR || CHECK_REG(vm->args.arg3.type, vm->args.arg3.readed)))
		{
			init_args(carriage, vm->map, &vm->args);
			addr = (vm->args.arg2.value + vm->args.arg3.value) % IDX_MOD;
			rev = vm->args.arg1.value;
			ft_byterev_ui32((unsigned int *)&rev);
			write_int_in_map(&rev, carriage->pc + addr, vm->map);
			res = 1;
		}
		vm->args.shift += vm->args.arg1.size + vm->args.arg2.size + vm->args.arg3.size;
	}
	return (res);
}
