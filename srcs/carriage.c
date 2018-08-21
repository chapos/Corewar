
#include "../includes/op.h"

int		del_cars(t_carriage **cars, int num_player)
{
	t_carriage *temp;
	t_carriage *temp2;

	temp = *cars;
	temp2 = NULL;
	while (temp)
	{
		if (temp->num_player == num_player)
		{
			if (temp2)
				temp2->next = temp->next;
			else
				*cars = temp->next;
			free(temp);
		}
		temp2 = temp;
		temp = temp->next;
	}
	return (0);
}

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
		ncar->life = 1;
		ncar->num_player = players->num_player;
		add_car(cars, ncar);
		players = players->next;
		i += ((64 / players_count)) * 64;
	}
	return (0);
}