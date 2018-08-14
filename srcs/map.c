
#include "op.h"

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

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
		player->num_player = 0;
		map[n] = player->code[i];
//		printf("%.2x ", vm->map[i]);
//		printf("%.2x ", vm->player->code[i]);
		i++;
		n++;
	}
	i = 0;
//	while (i < MEM_SIZE)
//	{
//		printf("%.2x ", map[i]);
//		i++;
//	}
	return (0);
}


int		write_in_map(unsigned char *map, t_list *players)
{
	unsigned int i;
	int players_count;

	i = 0;
	players_count = ft_lstlen(players);
	map_zero(map);
	while (players)
	{
		map_player(map, (t_player *)players->content, i);
		//ft_printf("%s\n", ((t_player *)(players->content))->head.prog_name);
		players = players->next;
		i += ((64 / players_count)) * 64;
		//write(1, "ZXC\n", 4);
	}

	return 0;
}
