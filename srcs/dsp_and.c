/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dsp_and.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 14:39:30 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/28 12:34:09 by rpetluk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void	print_and(t_carriage *carriage, t_args *args)
{
	print_pnum(carriage->num_car);
	ft_printf("and %d", args->arg1.value);
	ft_printf(" %d", args->arg2.value);
	ft_printf(" r%hhu\n", (unsigned char)args->arg3.readed);
	carriage = NULL;
}

int		dsp_and(t_carriage *carriage, t_vm *vm)
{
	unsigned char	acb;
	int				res;
	unsigned int	and;

	res = 0;
	acb = vm->map[(carriage->pc + 1) % MEM_SIZE];
	ft_memset(&vm->args, 0, sizeof(t_args));
	vm->args.shift = 1;
	if ((acb & ARG_MASK1) || (acb & ARG_MASK2) || (acb & ARG_MASK3))
	{
		read_args_from_map(carriage->pc, vm->map, &vm->args, (t_reader){read_int_from_map, read_short_from_map});
		if (vm->args.arg1.type == T_IND)
			vm->args.arg1.readed %= IDX_MOD;
		if (vm->args.arg2.type == T_IND)
			vm->args.arg2.readed %= IDX_MOD;
		if ((acb & ARG_MASK1) && (acb & ARG_MASK2) && CHECK_REG(vm->args.arg3.type, vm->args.arg3.readed))
		{
			init_args(carriage, vm->map, &vm->args);
			and = vm->args.arg1.value & vm->args.arg2.value;
			carriage->reg[vm->args.arg3.readed] = and;
			carriage->carry = and ? 0 : 1;
			res = 1;
		}
		vm->args.shift += vm->args.arg1.size + vm->args.arg2.size + vm->args.arg3.size;
	}
	return (res);
}
