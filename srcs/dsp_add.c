/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dsp_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 14:38:11 by oevtushe          #+#    #+#             */
/*   Updated: 2018/09/22 18:40:50 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void	print_add(t_carriage *carriage, t_vm *vm)
{
	print_pnum(carriage->num_car);
	printf("add r%hhu r%hhu r%hhu\n", (unsigned char)vm->args.arg1.readed,
			(unsigned char)vm->args.arg2.readed,
				(unsigned char)vm->args.arg3.readed);
}

/*
** name: add
** args: T_REG, T_REG, T_REG
** opcode: 4
** cycles: 10
** ACB: yes
** modifies carry
**
** Description:
**	Add two registers and store result into third register
*/

int		dsp_add(t_carriage *carriage, t_vm *vm)
{
	unsigned char	acb;
	int				res;
	unsigned int	sum;

	res = 0;
	acb = vm->map[(carriage->pc + 1) % MEM_SIZE];
	ft_memset(&vm->args, 0, sizeof(t_args));
	vm->args.shift = 1;
	if ((acb & ARG_MASK1) || (acb & ARG_MASK2) || (acb & ARG_MASK3))
	{
		read_args_from_map(carriage->pc, vm->map, &vm->args,
				(t_reader){read_int_from_map, read_short_from_map});
		if (validate_args(&vm->args, &vm->ops[3].pargs))
		{
			sum = carriage->reg[vm->args.arg1.readed] +
				carriage->reg[vm->args.arg2.readed];
			carriage->reg[vm->args.arg3.readed] = sum;
			carriage->carry = sum ? 0 : 1;
			res = 1;
		}
		vm->args.shift += vm->args.arg1.size + vm->args.arg2.size
			+ vm->args.arg3.size;
	}
	return (res);
}
