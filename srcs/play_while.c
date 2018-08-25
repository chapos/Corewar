/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_while.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 19:35:34 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/25 16:14:44 by oevtushe         ###   ########.fr       */
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
			{
				ft_printf("Player %d ", players->num_player);
				ft_printf("(%s) is said to be alive\n", players->head.prog_name);
			}
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

int play_cycle(t_vm *vm, int cycle, int *cycles, t_ama_dispatcher *dsp)
{
	int			pn;
	t_carriage	*tcars;
	int			times[16];
	int			ncycle;
	int			shift;
	t_args		args;
	int			res;
	int			cmd;

	ncycle = 1;
	init_dsp(dsp);
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
					tcars->count_live++;
					read_int_from_map(&pn, tcars->pc + 1, vm->map);
					tcars->life++;
					add_player_live(vm->players, tcars->num_player, vm->flags.v);
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
			tcars = tcars->next;
		}
		if (vm->flags.d && ncycle == vm->flags.d)
		{
			print_map(vm->map, vm->cars);
			char c;
			read(1, &c, 1);
		}
		cycle--;
		(*cycles)++;
		if (key_validate(vm->flags.v, 2))
			ft_printf("Is now cycle %d\n", *cycles);
		if (vm->flags.d == *cycles)
		{
			print_map(vm->map, vm->cars);
			free_all(vm);
		}
		if (vm->flags.s && (*cycles) % vm->flags.s == 0)
		{
			print_map(vm->map, vm->cars);
			usleep(10);
			char c;
			read(1, &c, 1);
		}
	}
	return (1);
}

int play_while(t_vm *vm)
{
	int 		cycle_to_die;
	int 		count_cycle;
	int 		count_live;
	t_ama_dispatcher dsp[16];
	int 		cycles;

	cycles = 0;
	count_cycle = 0;
	cycle_to_die = CYCLE_TO_DIE;
	init_dsp(dsp);

	while ((count_live = check_live(&vm->players)) && cycle_to_die > 0)
	{
		if ((count_cycle && count_cycle % MAX_CHECKS == 0) || count_live > NBR_LIVE)
		{
			cycle_to_die -= CYCLE_DELTA;
			ft_printf("Cycle to die is now %d\n", cycle_to_die);
		}
		play_cycle(vm, cycle_to_die, dsp, &cycles);
		count_cycle++;
		del_cars(&vm->cars, vm->flags.v);

	}
	return (0);
}
