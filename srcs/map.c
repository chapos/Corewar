/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 15:42:48 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/31 08:47:07 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

int		write_in_map(unsigned char *map, t_player *player)
{
	unsigned int	i;
	int				space;

	i = 0;
	space = MEM_SIZE / count_players(player);
	while (player)
	{
		ft_memcpy(&map[i], player->code, player->head.prog_size);
		player = player->next;
		i += space;
	}
	return (0);
}
