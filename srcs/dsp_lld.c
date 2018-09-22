/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dsp_lld.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 12:49:55 by oevtushe          #+#    #+#             */
/*   Updated: 2018/09/22 19:00:28 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void	print_lld(t_carriage *carriage, t_vm *vm)
{
	print_pnum(carriage->num_car);
	printf("lld %d r%hhu\n", vm->args.arg1.value,
		(unsigned char)vm->args.arg2.readed);
}

/*
** name: lld
** args: T_DIR | T_IND, T_REG
** opcode: 13
** cycles: 10
** ACB: yes
** modifies carry
**
** Description:
** 	Same as ld but without %IDX_MOD
*/

int		dsp_lld(t_carriage *carriage, t_vm *vm)
{
	unsigned char	acb;
	int				res;

	res = 0;
	acb = vm->map[(carriage->pc + 1) % MEM_SIZE];
	ft_memset(&vm->args, 0, sizeof(t_args));
	vm->args.shift = 1;
	if ((acb & ARG_MASK1) || (acb & ARG_MASK2))
	{
		read_args_from_map(carriage->pc, vm->map, &vm->args,
				(t_reader){read_int_from_map, read_short_from_map});
		if (validate_args(&vm->args, &vm->ops[12].pargs))
		{
			init_args(carriage, vm->map, &vm->args);
			if (vm->args.arg1.type == T_IND)
				vm->args.arg1.value >>= 16;
			carriage->reg[vm->args.arg2.readed] = vm->args.arg1.value;
			carriage->carry = vm->args.arg1.value == 0 ? 1 : 0;
			res = 1;
		}
		vm->args.shift += vm->args.arg1.size + vm->args.arg2.size;
	}
	return (res);
}
