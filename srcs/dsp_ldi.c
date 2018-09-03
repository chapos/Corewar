/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dsp_ldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 12:11:31 by oevtushe          #+#    #+#             */
/*   Updated: 2018/09/03 16:19:22 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void	print_ldi(t_carriage *carriage, t_vm *vm)
{
	int		sum;
	int		rf;

	sum = (vm->args.arg1.value + vm->args.arg2.value) % IDX_MOD;
	rf = carriage->pc + sum;
	print_pnum(carriage->num_car);
	printf("ldi %d %d r%hhu\n", vm->args.arg1.value,
			  vm->args.arg2.value, (unsigned char)vm->args.arg3.readed);
	printf("%6.0d | -> load from %d + %d = %d (with pc and mod %d)\n", 0,
			  vm->args.arg1.value, vm->args.arg2.value,
			  vm->args.arg1.value + vm->args.arg2.value, rf);
}

int		dsp_ldi(t_carriage *carriage, t_vm *vm)
{
	unsigned char	acb;
	int				res;
	int				val;

	res = 0;
	acb = vm->map[(carriage->pc + 1) % MEM_SIZE];
	ft_memset(&vm->args, 0, sizeof(t_args));
	vm->args.shift = 1;
	if ((acb & ARG_MASK1) || (acb & ARG_MASK2) || (acb & ARG_MASK3))
	{
		read_args_from_map(carriage->pc, vm->map, &vm->args,
				(t_reader){read_short_from_map, read_short_from_map});
		if (vm->args.arg1.type == T_IND)
			vm->args.arg1.readed %= IDX_MOD;
		if (validate_args(&vm->args, &vm->ops[9].pargs))
		{
			init_args(carriage, vm->map, &vm->args);
			val = (vm->args.arg1.value + vm->args.arg2.value) % IDX_MOD;
			read_int_from_map(&val, carriage->pc + val, vm->map);
			carriage->reg[vm->args.arg3.readed] = val;
			res = 1;
		}
		vm->args.shift += vm->args.arg1.size + vm->args.arg2.size
			+ vm->args.arg3.size;
	}
	return (res);
}
