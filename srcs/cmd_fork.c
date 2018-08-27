/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 11:02:29 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/27 15:02:33 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void	print_fork(t_carriage *carriage, t_args *args)
{
	int	val;

	val = (carriage->pc + args->arg1.value) % MEM_SIZE;
	print_pnum(carriage->num_car);
	ft_printf("fork %d (%d)\n", args->arg1.value, val);
}

int		cmd_fork(t_carriage *father, unsigned char *map, t_args *args, t_carriage **root, int process_counter)
{
	int			npos;
	t_carriage	*son;

	son = (t_carriage *)ft_memalloc(sizeof(t_carriage));
	ft_memset(args, 0, sizeof(t_args));
	ft_memcpy(son, father, sizeof(t_carriage));
	read_short_from_map(&npos, father->pc + 1, map);
	npos %= IDX_MOD;
	args->arg1.readed = npos;
	args->arg1.value = npos;
	son->pc = normalize_pc(npos + father->pc);
	son->num_car = process_counter;
	son->command = 0;
	add_car(root, son);
	/*
	father->pc += 3;
	father->pc %= MEM_SIZE;
	*/
	return (1);
}
