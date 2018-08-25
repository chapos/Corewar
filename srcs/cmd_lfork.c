/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lfork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 11:32:06 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/25 12:02:00 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void	print_lfork(t_carriage *carriage, t_args *args)
{
	int	val;

	val = (carriage->pc + args->arg1.value) % MEM_SIZE;
	ft_printf("lfork %d (%d)\n", args->arg1.value, val);
}

int		cmd_lfork(t_carriage *father, unsigned char *map, t_carriage **root)
{
	int			npos;
	t_carriage	*son;

	son = (t_carriage *)ft_memalloc(sizeof(t_carriage));
	ft_memcpy(son, father, sizeof(t_carriage));
	read_short_from_map(&npos, father->pc + 1, map);
	son->pc = father->pc + npos;
	son->pc %= MEM_SIZE;
	son->num_car = (*root)->num_car + 1;
	add_car(root, son);
	father->pc += 3;
	father->pc %= MEM_SIZE;
	return (1);
}
