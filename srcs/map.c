/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 15:42:48 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/30 12:55:56 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

int		write_in_map(unsigned char *map, t_player *player)
{
	unsigned int	i;
	int				space;

	i = 0;
	/*
	** Estb libnije funkcii je
	** map_zero(map);
	*/
	space = MEM_SIZE / count_players(player);
	while (player)
	{
		/*
		** Dlja etogo toze estb libnaja funkcija
		** map_player(map, player, i);
		*/
		ft_memcpy(&map[i], player->code, player->head.prog_size);
		player = player->next;
		/*
		** Esli igrokov 3, togda 64 / 3 = 21.3333, no y tebja int
		** poetomu 21, 21 * 64 = 1344, chto ne ravno 1365 = MEM_SIZE / 3;
		** i += ((64 / players_count)) * 64;
		*/
		i += space;
	}
	return (0);
}
