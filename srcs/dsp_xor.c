/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dsp_xor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 14:41:56 by oevtushe          #+#    #+#             */
/*   Updated: 2018/09/22 19:28:09 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void		print_xor(t_carriage *carriage, t_vm *vm)
{
	print_pnum(carriage->num_car);
	printf("xor %d %d r%hhu\n", vm->args.arg1.value,
			vm->args.arg2.value, (unsigned char)vm->args.arg3.readed);
}

static void	do_xor(t_carriage *carriage, t_vm *vm)
{
	int		xor;

	init_args(carriage, vm->map, &vm->args);
	xor = vm->args.arg1.value ^ vm->args.arg2.value;
	carriage->reg[vm->args.arg3.readed] = xor;
	carriage->carry = xor ? 0 : 1;
}

/*
** name: xor
** args: T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG
** opcode: 8
** cycles: 6
** ACB: yes
** modifies carry
**
** Description:
** 	Acts like 'and' with an exclusive OR
*/

int			dsp_xor(t_carriage *carriage, t_vm *vm)
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
				(t_reader){read_int_from_map, read_short_from_map});
		if (vm->args.arg1.type == T_IND)
			vm->args.arg1.readed %= IDX_MOD;
		if (vm->args.arg2.type == T_IND)
			vm->args.arg2.readed %= IDX_MOD;
		if (validate_args(&vm->args, &vm->ops[7].pargs))
		{
			do_xor(carriage, vm);
			res = 1;
		}
		vm->args.shift += vm->args.arg1.size +
			vm->args.arg2.size + vm->args.arg3.size;
	}
	return (res);
}
