/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_while.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 19:35:34 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/25 14:47:32 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

int		check_live(t_player **players, t_carriage **cars)
{
	t_player	*tplay;
	int value;
	int count;

	tplay = *players;
	count = 0;
	value = 0;
	cars = NULL;
	while (tplay)
	{
		count = tplay->live;
//		if (tplay->live == 0)
//		{
//			del_cars(cars, tplay->num_player);
//			del_plaeyr(players, tplay->num_player);
//		}
//		else
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

int play_cycle(t_vm *vm, int cycle, t_ama_dispatcher *dsp)
{
	int			pn;
	t_carriage	*tcars;
	int			times[16];
	int			ncycle;
	int			live;
	int			shift;
	t_args		args;
	int			res;
	int			cmd;

	live = 0;
	ncycle = 1;
	init_times(times);
	ft_memset(&args, 0, sizeof(t_args));
	while (cycle)
	{
		ft_printf("Is now cycle: %d\n", ncycle++);
		tcars = vm->cars;
		while (tcars)
		{
			if (is_time_to_run(vm->map[tcars->pc], tcars, times))
			{
				res = 0;
				shift = 0;
				if (EXS_DSP(vm->map[tcars->pc]))
				{
					cmd = vm->map[tcars->pc];
					res = dsp[cmd - 1].exec_cmd(tcars, vm->map, &args, &shift);
					if (res)
						dsp[cmd - 1].print_cmd(tcars, &args);
				}
				else if (vm->map[tcars->pc] == 1)
				{
					read_int_from_map(&pn, tcars->pc + 1, vm->map);
					ft_printf("live %d\n", pn);
					if (add_player_live(vm->players, pn))
						live++;
					shift = 4;
					res = 1;
				}
				else if (vm->map[tcars->pc] == 12)
				{
					res = cmd_fork(tcars, vm->map, &args, &vm->cars);
					print_fork(tcars, &args);
					shift = 2;
				}
				else if (vm->map[tcars->pc] == 15)
				{
					res = cmd_lfork(tcars, vm->map, &vm->cars);
					print_lfork(tcars, &args);
					shift = 2;
				}
				if (vm->map[tcars->pc] != 9)
					++tcars->pc;
				tcars->pc += shift;
				tcars->pc = normalize_pc(tcars->pc);
			}

//			ft_printf("Carry: %d\n", tcars->carry);
			tcars = tcars->next;
		}
		if (vm->flags.d && ncycle == vm->flags.d)
		{
			print_map(vm->map, vm->cars);
			char c;
			read(1, &c, 1);
		}
		cycle--;
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
	t_ama_dispatcher dsp[16];

	live = 0;
	count_cycle = 1;
	cycle_to_die = CYCLE_TO_DIE;
	init_dsp(dsp);

	while (live || (count_live = check_live(&vm->players, &vm->cars)))
	{
		if (cycle_to_die < 1)
			free_all(vm);
		cycle = cycle_to_die;
		if (count_cycle % MAX_CHECKS == 0 || count_live > NBR_LIVE)
			cycle_to_die /= CYCLE_DELTA;
		live = play_cycle(vm, cycle, dsp);
		count_cycle++;
		//print_map(vm->map, vm->cars);
		//ft_printf("%d\n", count_cycle);
	}
	while (vm->cars)
		vm->cars = vm->cars->next;
	return (0);
}
