/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 15:11:47 by oevtushe          #+#    #+#             */
/*   Updated: 2018/09/17 16:00:37 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

static void	del_car(t_carriage **cars, t_carriage **del, t_carriage **temp2)
{
	if (*del == *cars)
	{
		*cars = (*cars)->next;
		*temp2 = *cars;
		free(*del);
		*del = *cars;
	}
	else
	{
		(*temp2)->next = (*del)->next;
		free(*del);
		*del = (*temp2)->next;
	}
}

void		del_cars(t_vm *vm, int ctd)
{
	t_carriage	*temp;
	t_carriage	*temp2;

	temp = vm->cars;
	while (temp)
		if (temp->life == 0 || ctd < 0)
		{
			if (vm->flags.v & 8)
				printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
					temp->num_car, vm->game_cycle - temp->last_live_cn, ctd);
			if (vm->flags.visual)
				vdel_car(vm, temp);
			del_car(&vm->cars, &temp, &temp2);
		}
		else
		{
			temp->life = 0;
			temp2 = temp;
			temp = temp->next;
		}
}

void		add_car(t_carriage **cars, t_carriage *car)
{
	if (*cars)
		car->next = *cars;
	*cars = car;
}

int			player_create_car(t_player *players, t_carriage **cars)
{
	int			players_count;
	t_carriage	*ncar;
	int			i;
	int			space;

	i = 0;
	players_count = count_players(players);
	space = MEM_SIZE / players_count;
	while (players)
	{
		ncar = (t_carriage *)ft_memalloc(sizeof(t_carriage));
		ncar->pc_prev = -1;
		ncar->pc = i;
		if (*cars)
			ncar->num_car = (*cars)->num_car + 1;
		else
			ncar->num_car = 1;
		ncar->wait = -1;
		ncar->reg[1] = players->num_player;
		ncar->num_player = players->num_player;
		add_car(cars, ncar);
		players = players->next;
		i += space;
	}
	return (0);
}
