/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_while.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 19:35:34 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/21 19:58:04 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

int		count_cars(t_carriage *cars)
{
	int		count;

	count = 0;
	while (cars)
	{
		cars = cars->next;
		count++;
	}
	ft_printf("count cars = %d\n", count);
	return (count);
}

int		check_live(t_player **players)
{
	t_player	*tplay;
	int value;
	int count;

	tplay = *players;
	count = 0;
	value = 0;
	while (tplay)
	{
		count = tplay->live;
		tplay->live = 0;
		if (count > value)
			value = count;
		tplay = tplay->next;
	}
	return (value);
}

int add_player_live(t_player *players, int num_player, int v)
{
	while (players)
	{
		if (players->num_player == num_player)
		{
			if (key_validate(v, 1))
			ft_printf("Player %d (%s) is said to be alive\n", players->num_player, players->head.prog_name);
			players->live++;
			return (0);
		}
		players = players->next;
	}
	return (1);
}

int		is_time_to_run(int op, t_carriage *carriage, int *times)
{
	int		res;

	res = 0;
	if (carriage->wait > 0)
		--carriage->wait;
	else if (carriage->wait == -1 && op)
		carriage->wait = times[op - 1] - 2;
	else
	{
		carriage->wait = -1;
		res = 1;
	}
	return (res);
}

void	init_times(int *times)
{
	times[0] = 10;
	times[1] = 5;
	times[2] = 5;
	times[3] = 10;
	times[4] = 10;
	times[5] = 6;
	times[6] = 6;
	times[7] = 6;
	times[8] = 20;
	times[9] = 25;
	times[10] = 25;
	times[11] = 800;
	times[12] = 10;
	times[13] = 50;
	times[14] = 1000;
	times[15] = 2;
}

int play_cycle(t_vm *vm, int cycle, int *cycles)
{
	int			pn;
	t_carriage	*tcars;
	int			(*dsp[16])(t_carriage*, unsigned char*);
	int			times[16];
	int			live;

	live = 0;
	init_dsp(dsp);
	init_times(times);
	while (cycle)
	{
		tcars = vm->cars;
		while (tcars)
		{
			if (is_time_to_run(vm->map[tcars->pc], tcars, times))
			{

				if (vm->map[tcars->pc] - 1 > 0 && vm->map[tcars->pc] - 1 < 16 &&
						dsp[vm->map[tcars->pc] - 1])
					dsp[vm->map[tcars->pc] - 1](tcars, vm->map);
				else if (vm->map[tcars->pc] == 1)
				{
					tcars->count_live++;
					read_int_from_map(&pn, tcars->pc + 1, vm->map);
					tcars->life++;
					if (add_player_live(vm->players, pn, vm->flags.v))
						live++;
					tcars->pc
							+= 5;
					tcars->pc %= MEM_SIZE;
				}
				else if (vm->map[tcars->pc] == 12)
					cmd_fork(tcars, vm->map, &vm->cars);
				else if (vm->map[tcars->pc] == 15)
					cmd_lfork(tcars, vm->map, &vm->cars);
				else
				{
					++tcars->pc;
					tcars->pc %= MEM_SIZE;
				}

			}
			tcars = tcars->next;
		}
		cycle--;
		(*cycles)++;
		if (key_validate(vm->flags.v, 2))
			ft_printf("Is now cycles %d\n", *cycles);
		if (vm->flags.d == *cycles)
		{
			print_map(vm->map, vm->cars);
			free_all(vm);
		}
		if (vm->flags.s && (*cycles) % vm->flags.s == 0)
		{
			print_map(vm->map, vm->cars);
			ft_printf("%d\n", *cycles);
			usleep(10);
			char c;
			read(1, &c, 1);
		}
	}
	return (live);
}

int play_while(t_vm *vm)
{
	int 		cycle;
	int 		cycle_to_die;
	int 		count_cycle;
	int 		count_live;
	int			live;
	int 		cycles;

	cycles = 0;
	live = 0;
	count_cycle = 1;
	cycle_to_die = CYCLE_TO_DIE;

	while (live || (count_live = check_live(&vm->players)))
	{
		if (cycle_to_die < 1)
			free_all(vm);
		del_cars(&vm->cars, vm->flags.v);
		cycle = cycle_to_die;
		if (count_cycle % MAX_CHECKS == 0 || count_live > NBR_LIVE)
			cycle_to_die /= CYCLE_DELTA;
		live = play_cycle(vm, cycle, &cycles);
		count_cycle++;
		//print_map(vm->map, vm->cars);
		//ft_printf("%d\n", count_cars(vm->cars));
	}
	return (0);
}
