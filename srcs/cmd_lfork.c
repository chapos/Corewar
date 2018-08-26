/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lfork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 11:32:06 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/26 19:10:19 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void	print_lfork(t_carriage *carriage, t_args *args)
{
	int	val;

	val = (carriage->pc + args->arg1.value) % MEM_SIZE;
	ft_printf("P%5d | lfork %d (%d)\n", carriage->num_car, args->arg1.value, val);
}

int		cmd_lfork(t_carriage *father, unsigned char *map, t_carriage **root, t_args *args, int process_counter)
{
	int			npos;
	t_carriage	*son;

	son = (t_carriage *)ft_memalloc(sizeof(t_carriage));
	ft_memset(args, 0, sizeof(t_args));
	ft_memcpy(son, father, sizeof(t_carriage));
	read_short_from_map(&npos, father->pc + 1, map);
	args->arg1.readed = npos;
	args->arg1.value = npos;
	son->pc = normalize_pc(npos + father->pc);
	son->num_car = process_counter;
	son->command = 0;
	add_car(root, son);
	return (1);
}
