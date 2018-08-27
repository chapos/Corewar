/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_while.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 19:35:34 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/27 16:56:30 by oevtushe         ###   ########.fr       */
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
	else if (carriage->wait == -1 && (op >= 1 && op <= 16))
	{
		carriage->wait = times[op - 1] - 2;
		carriage->command = op;
	}
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

int play_cycle(t_vm *vm, int cycle, int *cycles, t_ama_dispatcher *dsp, int *process_counter)
{
	int			pn;
	t_carriage	*tcars;
	int			times[16];
	int			ncycle;
	int			shift;
	t_args		args;
	int			res;

	ncycle = 1;
	init_dsp(dsp);
	init_times(times);
	ft_memset(&args, 0, sizeof(t_args));
	while (cycle)
	{
		tcars = vm->cars;
		if (key_validate(vm->flags.v, 2))
			ft_printf("It is now cycle %d\n", *cycles + 1);
		while (tcars)
		{
			tcars->reg[1] = -1;
			if (is_time_to_run(vm->map[tcars->pc], tcars, times))
			{
				res = 0;
				shift = 0;
				if (EXS_DSP(tcars->command))
				{
					res = dsp[tcars->command - 1].exec_cmd(tcars, vm->map, &args, &shift);
					if (res || tcars->command == 9)
						dsp[tcars->command - 1].print_cmd(tcars, &args);
				}
				else if (tcars->command == 1)
				{
					tcars->count_live++;
					read_int_from_map(&pn, tcars->pc + 1, vm->map);
					tcars->life++;
					add_player_live(vm->players, tcars->num_player, vm->flags.v);
					print_pnum(tcars->num_car);
					ft_printf("live %d\n", pn);
					tcars->last_live_cn = *cycles;
					shift = 4;
					res = 1;
				}
				else if (tcars->command == 12)
				{
					res = cmd_fork(tcars, vm->map, &args, &vm->cars, ++(*process_counter));
					print_fork(tcars, &args);
					shift = 2;
				}
				else if (tcars->command == 15)
				{
					res = cmd_lfork(tcars, vm->map, &vm->cars, &args, ++(*process_counter));
					print_lfork(tcars, &args);
					shift = 2;
				}
				if (tcars->command != 9 || (tcars->command == 9 && !res))
				{
					if (tcars->command >= 1 && tcars->command <= 16)
						print_pc_movement(tcars->pc, shift, vm->map);
					++tcars->pc;
				}
				tcars->pc += shift;
				tcars->pc = normalize_pc(tcars->pc);
				tcars->command = 0;
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
	t_ama_dispatcher dsp[16];
	int 		cycles;
	int			process_counter;
	int			live;

	cycles = 0;
	count_cycle = 0;
	cycle_to_die = CYCLE_TO_DIE;
	live = 1;
	init_dsp(dsp);
	//
	process_counter = vm->cars->num_car;
	//
	while (live && cycle_to_die > 0)
	{
		play_cycle(vm, cycle_to_die, &cycles, dsp, &process_counter);
		// here because cars are killed before changing ctd
		del_cars(vm, cycle_to_die, cycles - 1, 0);
		if (((live = check_live(&vm->players)) >= NBR_LIVE) || CHECK_MC(count_cycle))
		{
			cycle_to_die -= CYCLE_DELTA;
			ft_printf("Cycle to die is now %d\n", cycle_to_die);
			count_cycle = 0;
		}
		count_cycle++;
	}
	del_cars(vm, cycle_to_die, cycles, 1);
	return (0);
}
