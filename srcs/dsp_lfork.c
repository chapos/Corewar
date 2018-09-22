/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dsp_lfork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 18:37:19 by oevtushe          #+#    #+#             */
/*   Updated: 2018/09/22 18:54:00 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

void	print_lfork(t_carriage *carriage, t_vm *vm)
{
	int	val;

	val = carriage->pc + vm->args.arg1.value;
	print_pnum(carriage->num_car);
	printf("lfork %d (%d)\n", vm->args.arg1.value, val);
}

/*
** name: lfork
** args: T_DIR
** opcode: 15
** cycles: 1000
** ACB: yes
**
** Description:
** 	Same as fork without modulo in the address
*/

int		dsp_lfork(t_carriage *father, t_vm *vm)
{
	int			npos;
	t_carriage	*son;

	son = (t_carriage *)ft_memalloc(sizeof(t_carriage));
	ft_memset(&vm->args, 0, sizeof(t_args));
	ft_memcpy(son, father, sizeof(t_carriage));
	read_short_from_map(&npos, father->pc + 1, vm->map);
	vm->args.arg1.readed = npos;
	vm->args.arg1.value = npos;
	son->pc_prev = -1;
	son->pc = normalize_pc(npos + father->pc);
	son->command = 0;
	son->num_car = ++vm->process_counter;
	vm->args.shift = 2;
	add_car(&vm->cars, son);
	return (1);
}
