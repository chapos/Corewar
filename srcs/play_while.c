/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_while.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 19:35:34 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/30 10:48:23 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

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

int play_cycle(t_vm *vm, int cycle, t_ama_dispatcher *dsp, int *times)
{
	t_carriage	*tcars;
	int			res;

	ft_memset(&vm->args, 0, sizeof(t_args));
	while (cycle)
	{
		vm->game_cycle++;
		tcars = vm->cars;
		if (vm->flags.v & 2)
		{
			write(1, "It is now cycle ", 16);
			ft_putnbr(vm->game_cycle);
			write(1, "\n", 1);
		}
		while (tcars)
		{
			//tcars->reg[1] = -1; // FIX THIS !
			if (is_time_to_run(vm->map[tcars->pc], tcars, times))
			{
				res = 0;
				vm->args.shift = 0;
				if (EXS_DSP(tcars->command))
				{
					res = dsp[tcars->command - 1].exec_cmd(tcars, vm);
					if ((res || tcars->command == 9) && vm->flags.v & 4)
						dsp[tcars->command - 1].print_cmd(tcars, vm);
				}
				if (tcars->command != 9 || (tcars->command == 9 && !res))
				{
					if (EXS_DSP(tcars->command) && vm->flags.v & 16)
						print_pc_movement(tcars->pc, vm->args.shift, vm->map);
					++tcars->pc;
				}
				tcars->pc += vm->args.shift;
				tcars->pc = normalize_pc(tcars->pc);
				tcars->command = 0;
			}
			tcars = tcars->next;
		}
		cycle--;
		if (vm->flags.d == vm->game_cycle)
		{
			print_map(vm->map, vm->cars);
			free_all(vm);
		}
		if (vm->flags.s && vm->game_cycle % vm->flags.s == 0)
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
	int			times[16];
	int			live;

	count_cycle = 0;
	cycle_to_die = CYCLE_TO_DIE;
	live = 1;
	init_dsp(dsp);
	init_times(times);
	vm->process_counter = vm->cars->num_car;
	while (vm->lives_in_cur_period && cycle_to_die > 0)
	{
		vm->lives_in_cur_period = 0;
		play_cycle(vm, cycle_to_die, dsp, times);
		del_cars(vm, cycle_to_die, 0);
		//if (((live = check_live(&vm->players)) >= NBR_LIVE) || CHECK_MC(count_cycle))
		if (vm->lives_in_cur_period >= NBR_LIVE || CHECK_MC(count_cycle))
		{
			cycle_to_die -= CYCLE_DELTA;
			if (vm->flags.v & 2)
			{
				write(1, "Cycle to die is now ", 20);
				ft_putnbr(cycle_to_die);
				write(1, "\n", 1);
			}
			count_cycle = 0;
		}
		count_cycle++;
	}
	if (cycle_to_die < 1)
	{
		play_cycle(vm, 1, dsp, times);
//		if (vm->flags.v & 2)
//		{
//			write(1, "Cycle to die is now ", 20);
//			ft_putnbr(cycle_to_die);
//			write(1, "\n", 1);
//		}
	}
	del_cars(vm, cycle_to_die, 1);
	print_winner(vm->players, vm->winner);
	free_all(vm);
	return (0);
}
