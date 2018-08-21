/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_while.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 19:35:34 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/21 16:47:57 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

//int count_live_player(t_carriage *cars, int num_player)
//{
//	int count;
//
//	count = 0;
//	while (cars)
//	{
//		if (num_player == cars->num_player && cars->life)
//		{
//			count++;
//			cars->life = 0;
//		}
//		cars = cars->next;
//	}
//	return (count);
//}

int		check_live(t_player **players, t_carriage **cars)
{
	t_player	*tplay;
	int value;
	int count;

	tplay = *players;
	count = 0;
	while (tplay)
	{
		//count = count_live_player(cars, players->num_player);
		count = tplay->live;
		if (tplay->live == 0)
		{
			del_cars(cars, tplay->num_player);
			del_plaeyr(players, tplay->num_player);
		}
		else
			tplay->live = 0;
		if (count > value)
			value = count;
		tplay = tplay->next;
	}
	return (value);
}

int add_player_live(t_player *players, int num_player)
{
	while (players)
	{
		if (players->num_player == num_player)
		{
			players->live++;
			return (1);
		}
		players = players->next;
	}
	return (0);
}

int play_cycle(t_vm *vm, int cycle)
{
	// player number
	int			pn;
	t_carriage	*tcars;
	int			(*dsp[16])(t_carriage*, unsigned char*);

	init_dsp(dsp);
	while (cycle)
	{
		tcars = vm->cars;
		while (tcars)
		{
			if (vm->map[tcars->pc] - 1 > 0 && vm->map[tcars->pc] - 1 < 16 &&
					dsp[vm->map[tcars->pc] - 1])
			{
				dsp[vm->map[tcars->pc] - 1](tcars, vm->map);
			}
			else if (vm->map[tcars->pc] == 1)
			{
				// live
//				cmd_live(tcars, vm->map, &pn);
				read_int_from_map(&pn, tcars->pc + 1, vm->map);
				add_player_live(vm->players, pn);
//				ft_printf("i alive: %d\n", pn);
				tcars->pc += 5;
				tcars->pc %= MEM_SIZE;
				// increase live counter for player with 'pn' number
			}
			else if (vm->map[tcars->pc] == 12)
			{
				// fork
				// pass pointer at pointer at the begining of the list of carriages
				// instead of HERE
				cmd_fork(tcars, vm->map, &vm->cars);
			}
			else if (vm->map[tcars->pc] == 15)
			{
				// lfork
				// the same as with fork
				cmd_lfork(tcars, vm->map, &vm->cars);
			}
			tcars = tcars->next;
		}
		cycle--;
		//print_map(vm->map);
	}
	return (0);
}

int play_while(t_vm *vm)
{
	int 		cycle;
	int 		cycle_to_die;
	int 		count_cycle;
	int 		count_live;

	count_cycle = 0;
	cycle_to_die = CYCLE_TO_DIE;

	while ((count_live = check_live(&vm->players, &vm->cars)) && cycle_to_die > 1)
	{
		cycle = cycle_to_die;
		if (count_cycle == MAX_CHECKS || count_live > NBR_LIVE)
			cycle_to_die /= CYCLE_DELTA;
		play_cycle(vm, cycle);
		count_cycle++;
		print_map(vm->map, vm->cars);
	}
	return (0);
}

//int play_start(t_vm *vm)
//{
//
//}
