/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dsp_zjmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 14:55:22 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/19 11:31:08 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

int		dsp_zjmp(t_carriage *carriage, unsigned char *map)
{
	int			res;
	int			val;

	val = 1;
	res = 0;
	if (carriage->carry)
	{
		read_short_from_map(&val, carriage->pc + 1, map);
		res = 1;
	}
	carriage->pc += val; // val % IDX_MOD;
	carriage->pc %= MEM_SIZE;
	if (carriage->pc < 0)
		carriage->pc = MEM_SIZE + carriage->pc;
	return (res);
}