/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dsp_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 14:40:02 by oevtushe          #+#    #+#             */
/*   Updated: 2018/09/23 11:02:06 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void		print_or(t_carriage *carriage, t_vm *vm)
{
	print_pnum(carriage->num_car);
	printf("or %d %d r%hhu\n", vm->args.arg1.value, vm->args.arg2.value,
			(unsigned char)vm->args.arg3.readed);
}

static void	do_or(t_carriage *carriage, t_vm *vm)
{
	unsigned int	or;

	init_args(carriage, vm->map, &vm->args);
	or = vm->args.arg1.value | vm->args.arg2.value;
	carriage->reg[vm->args.arg3.readed] = or;
	carriage->carry = or ? 0 : 1;
}

/*
** name: or
** args: T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG
** opcode: 7
** cycles: 6
** ACB: yes
** modifies carry
**
** Descrioption:
** 	bit-to-bit OR
*/

int			dsp_or(t_carriage *carriage, t_vm *vm)
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
		if (validate_args(&vm->args, &vm->ops[6].pargs))
		{
			do_or(carriage, vm);
			res = 1;
		}
		vm->args.shift += vm->args.arg1.size +
			vm->args.arg2.size + vm->args.arg3.size;
	}
	return (res);
}
