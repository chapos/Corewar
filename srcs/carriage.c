/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 15:11:47 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/21 19:59:20 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/op.h"

int		del_cars(t_carriage **cars)
{
	t_carriage *temp;
	t_carriage *temp2;

	temp = *cars;
	while (temp)
		if (temp->life == 0)
			if (temp == *cars)
			{
				*cars = temp->next;
				temp2 = *cars;
				free(temp);
				temp = *cars;
			}
			else
			{
				temp2->next = temp->next;
				free(temp);
				temp = temp2->next;
			}
		else
		{
			temp2 = temp;
			temp = temp->next;
		}
	return (0);
}

//int		del_cars(t_carriage **cars)
//{
//	t_carriage *temp;
//	t_carriage *temp2;
//
//	temp = *cars;
//	temp2 = NULL;
//	while (temp)
//	{
//		if (temp->life == 0)
//		{
//			x = temp;
//			if (temp2)
//				temp2->next = temp->next;
//			else
//				*cars = temp->next;
////			free(temp);
//		}
//		else
//			temp->life = 0;
//		temp2 = temp;
//		temp = temp->next;
//		if (x)
//			free(temp);
//	}
//	ft_printf("ASD\n");
//	return (0);
//}

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
		//
		ncar->wait = -1;
		//
		ncar->reg[1] = players->num_player;
		ncar->num_player = players->num_player;
		add_car(cars, ncar);
		players = players->next;
		i += ((64 / players_count)) * 64;
	}
	return (0);
}
