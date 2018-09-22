/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dsp_sub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 14:38:57 by oevtushe          #+#    #+#             */
/*   Updated: 2018/09/22 19:26:04 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void	print_sub(t_carriage *carriage, t_vm *vm)
{
	print_pnum(carriage->num_car);
	printf("sub r%hhu r%hhu r%hhu\n", (unsigned char)vm->args.arg1.readed,
		(unsigned char)vm->args.arg2.readed,
		(unsigned char)vm->args.arg3.readed);
}

/*
** name: sub
** args: T_REG, T_REG, T_REG
** opcode: 5
** cycles: 10
** ACB: yes
** modifies carry
**
** Description:
** 	Same as add but uses substraction
*/

int		dsp_sub(t_carriage *carriage, t_vm *vm)
{
	unsigned char	acb;
	int				res;
	unsigned int	sub;

	res = 0;
	acb = vm->map[(carriage->pc + 1) % MEM_SIZE];
	ft_memset(&vm->args, 0, sizeof(t_args));
	vm->args.shift = 1;
	if ((acb & ARG_MASK1) || (acb & ARG_MASK2) || (acb & ARG_MASK3))
	{
		read_args_from_map(carriage->pc, vm->map, &vm->args,
				(t_reader){read_int_from_map, read_short_from_map});
		if (validate_args(&vm->args, &vm->ops[4].pargs))
		{
			sub = carriage->reg[vm->args.arg1.readed] -
				carriage->reg[vm->args.arg2.readed];
			carriage->reg[vm->args.arg3.readed] = sub;
			carriage->carry = sub ? 0 : 1;
			res = 1;
		}
		vm->args.shift += vm->args.arg1.size +
			vm->args.arg2.size + vm->args.arg3.size;
	}
	return (res);
}
