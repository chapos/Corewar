/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dsp_aff.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 14:17:04 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/29 18:05:42 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void	print_aff(t_carriage *carriage, t_vm *vm)
{
	carriage = NULL;
	vm = NULL;
}

int		dsp_aff(t_carriage *carriage, t_vm *vm)
{
	unsigned char	acb;
	int				res;

	res = 0;
	acb = vm->map[(carriage->pc + 1) % MEM_SIZE];
	ft_memset(&vm->args, 0, sizeof(t_args));
	vm->args.shift = 1;
	if ((acb & ARG_MASK1))
	{
		read_args_from_map(carriage->pc, vm->map, &vm->args, (t_reader){read_int_from_map, read_short_from_map});
		if (CHECK_REG(vm->args.arg1.type, vm->args.arg1.readed))
		{
			ft_putstr("Aff: ");
			ft_putchar((char)carriage->reg[vm->args.arg1.readed]);
			ft_putchar('\n');
			res = 1;
		}
		vm->args.shift += vm->args.arg1.size;
	}
	return (res);
}
