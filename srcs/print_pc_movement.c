/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pc_movement.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 19:22:31 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/26 19:16:18 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

static void	print_cmd(unsigned char *map, int size)
{
	int		i;

	i = 0;
	while (i < size)
		printf("%.2x ", (int)map[i++]);
}

void		print_pc_movement(int cur_pos, int shift, unsigned char *map)
{
	int		new_pos;

	shift += 1;
	new_pos = (cur_pos + shift) % MEM_SIZE;
	if (!cur_pos)
		printf("ADV %d (0x0000 -> %#.4x) ", shift, cur_pos + shift);
	else
		printf("ADV %d (%#.4x -> %#.4x) ", shift, cur_pos, cur_pos + shift);
	if (new_pos >= cur_pos)
	{
		print_cmd(&map[cur_pos], shift);
		printf("\n");
	}
	else
	{
		print_cmd(&map[cur_pos], MEM_SIZE - cur_pos);
		print_cmd(map, shift - (MEM_SIZE - cur_pos));
		printf("\n");
	}
}
