/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dsp_lldi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 12:53:52 by oevtushe          #+#    #+#             */
/*   Updated: 2018/09/22 19:07:16 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void		print_lldi(t_carriage *carriage, t_vm *vm)
{
	int		sum;
	int		rf;

	sum = vm->args.arg1.value + vm->args.arg2.value;
	rf = carriage->pc + sum;
	print_pnum(carriage->num_car);
	printf("lldi %d %d r%hhu\n", vm->args.arg1.value,
			vm->args.arg2.value, (unsigned char)vm->args.arg3.readed);
	printf("%6.0d | -> load from %d + %d = %d (with pc %d)\n", 0,
			vm->args.arg1.value, vm->args.arg2.value,
			sum, rf);
}

static void	do_lldi(t_carriage *carriage, t_vm *vm)
{
	int		val;

	init_args(carriage, vm->map, &vm->args);
	val = vm->args.arg1.value + vm->args.arg2.value;
	read_int_from_map(&val, carriage->pc + val, vm->map);
	carriage->carry = val ? 0 : 1;
	carriage->reg[vm->args.arg3.readed] = val;
}

/*
** name: lldi
** args: T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG
** opcode: 14
** cycles: 50
** ACB: yes
** modifies carry
**
** Description:
** 	Same as ldi, but doesn't apply any modulo to the addresses
*/

int			dsp_lldi(t_carriage *carriage, t_vm *vm)
{
	unsigned char	acb;
	int				res;

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
		if (validate_args(&vm->args, &vm->ops[13].pargs))
		{
			do_lldi(carriage, vm);
			res = 1;
		}
		vm->args.shift += vm->args.arg1.size +
			vm->args.arg2.size + vm->args.arg3.size;
	}
	return (res);
}
