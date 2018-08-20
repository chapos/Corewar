
#include "../includes/op.h"

void add_car(t_carriage **cars, t_carriage *car)
{
	if (*cars)
		car->next = *cars;
	*cars = car;
}

int player_create_car(t_player *players, t_carriage **cars)
{
	int players_count;
	t_carriage	*ncar;
	int i;

	i = 0;
	players_count = count_players(players);
	while (players)
	{
		ncar = (t_carriage *)ft_memalloc(sizeof(t_carriage));
		ncar->pc = i;
		ncar->num_player = players->num_player;
		add_car(cars, ncar);
		players = players->next;
		i += ((64 / players_count)) * 64;
	}
	return (0);
}