/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dsp_fork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 18:06:38 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/29 18:07:04 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

void	print_fork(t_carriage *carriage, t_vm *vm)
{
	int	val;

	val = (carriage->pc + (vm->args.arg1.readed % IDX_MOD)) % MEM_SIZE;
	print_pnum(carriage->num_car);
	ft_printf("fork %d (%d)\n", vm->args.arg1.readed, val);
}

int		dsp_fork(t_carriage *father, t_vm *vm)
{
	int			npos;
	t_carriage	*son;

	son = (t_carriage *)ft_memalloc(sizeof(t_carriage));
	ft_memset(&vm->args, 0, sizeof(t_args));
	ft_memcpy(son, father, sizeof(t_carriage));
	read_short_from_map(&npos, father->pc + 1, vm->map);
	vm->args.arg1.readed = npos;
	son->pc = normalize_pc((npos % IDX_MOD) + father->pc);
	son->num_car = ++vm->process_counter;
	son->command = 0;
	add_car(&vm->cars, son);
	vm->args.shift = 2;
	return (1);
}
