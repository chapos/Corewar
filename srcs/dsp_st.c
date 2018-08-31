/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dsp_st.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 14:37:28 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/29 18:11:29 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void	print_st(t_carriage *carriage, t_vm *vm)
{
	print_pnum(carriage->num_car);
	ft_putstr("st");
	if (vm->args.arg2.type == T_IND)
		printf(" r%d %d\n", (unsigned char)vm->args.arg1.readed, vm->args.arg2.value);
	else
		printf(" r%d %hhu\n", (unsigned char)vm->args.arg1.readed, (unsigned char)vm->args.arg2.readed);
	carriage = NULL;
}

int		dsp_st(t_carriage *carriage, t_vm *vm)
{
	unsigned char	acb;
	int				res;
	int				rev;
	int				tmp;

	tmp = 0;
	res = 0;
	acb = vm->map[(carriage->pc + 1) % MEM_SIZE];
	ft_memset(&vm->args, 0, sizeof(t_args));
	vm->args.shift = 1;
	// '||' because of ACB Invalid cases
	if ((acb & ARG_MASK1) || (acb & ARG_MASK2))
	{
		read_args_from_map(carriage->pc, vm->map, &vm->args, (t_reader){read_int_from_map, read_short_from_map});
		if (vm->args.arg2.type == T_IND)
		{
			tmp = vm->args.arg2.readed;
			vm->args.arg2.readed %= IDX_MOD;
		}
		if (CHECK_REG(vm->args.arg1.type, vm->args.arg1.readed) && (vm->args.arg2.type == T_IND ||
				vm->args.arg2.type == T_REG))
		{
			init_args(carriage, vm->map, &vm->args);
			if (vm->args.arg2.type == T_REG)
			{
				carriage->reg[vm->args.arg2.readed] = vm->args.arg1.value;
				res = 1;
			}
			else
			{
				rev = vm->args.arg1.value;
				ft_byterev_ui32((unsigned int *)&rev);
				write_int_in_map(&rev, carriage->pc + vm->args.arg2.readed, vm->map);
				res = 1;
			}
		}
		vm->args.shift += vm->args.arg1.size + vm->args.arg2.size;
		vm->args.arg2.value = tmp;
	}
	return (res);
}
