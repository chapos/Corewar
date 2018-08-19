/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 15:42:48 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/19 15:42:52 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

int		map_zero(unsigned char *map)
{
	int i;

	i = 0;
	while (i < MEM_SIZE)
	{
		map[i] = 0;
		i++;
	}
	return (0);
}

int 	map_player(unsigned char *map, t_player *player, unsigned int n)
{
	unsigned int i;

	i = 0;
	while (i < player->head.prog_size)
	{
		map[n] = player->code[i];
		i++;
		n++;
	}
	i = 0;
	return (0);
}


int		write_in_map(unsigned char *map, t_player *player)
{
	unsigned int i;
	int players_count;

	i = 0;
	players_count = count_players(player);
	map_zero(map);
	while (player)
	{
		map_player(map, player, i);
		player = player->next;
		i += ((64 / players_count)) * 64;
	}

	return 0;
}
