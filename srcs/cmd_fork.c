/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 11:02:29 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/21 16:38:40 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

int		cmd_fork(t_carriage *father, unsigned char *map, t_carriage **root)
{
	int			npos;
	t_carriage	*son;

	son = (t_carriage *)ft_memalloc(sizeof(t_carriage));
	ft_memcpy(son, father, sizeof(t_carriage));
	read_short_from_map(&npos, father->pc + 1, map);
	son->pc = npos + father->pc;
	son->pc %= MEM_SIZE;
	add_car(root, son);
	father->pc += 3;
	father->pc %= MEM_SIZE;
	return (1);
}
