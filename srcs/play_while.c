/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_while.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 19:35:34 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/31 18:33:31 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

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

void	while_tcars(t_carriage *tcars, t_vm *vm, t_ama_dispatcher *dsp, int *times)
{
	int res;

	while (tcars)
	{
		if (is_time_to_run(vm->map[tcars->pc], tcars, times))
		{
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
}

void	play_cycle(t_vm *vm, int cycle, t_ama_dispatcher *dsp, int *times)
{
	t_carriage	*tcars;

	ft_memset(&vm->args, 0, sizeof(t_args));
	while (cycle)
	{
		vm->game_cycle++;
		tcars = vm->cars;
		if (vm->flags.v & 2)
			printf("It is now cycle %d\n", vm->game_cycle);
		while_tcars(tcars, vm, dsp, times);
		cycle--;
		if (vm->flags.d == vm->game_cycle)
		{
			print_map(vm->map, vm->cars);
			free_all(vm);
		}
		if (vm->flags.s && vm->game_cycle % vm->flags.s == 0)
		{
			print_map(vm->map, vm->cars);
			char c;
			read(1, &c, 1);
		}
	}
}

void		ctd_operator(int licp, int *count_cycle, int *ctd, t_flags *flags)
{
	if (licp >= NBR_LIVE || CHECK_MC(*count_cycle))
	{
		*ctd -= CYCLE_DELTA;
		if (flags->v & 2)
		{
			printf("Cycle to die is now %d\n", *ctd);
		}
		*count_cycle = 0;
	}
}

void		play_while(t_vm *vm)
{
	int			cycle_to_die;
	int			count_cycle;
	t_ama_dispatcher dsp[16];
	int			times[16];

	count_cycle = 1;
	cycle_to_die = CYCLE_TO_DIE;
	init_dsp(dsp);
	init_times(times);
	vm->process_counter = vm->cars->num_car;
	while (vm->lives_in_cur_period && cycle_to_die > 0)
	{
		vm->lives_in_cur_period = 0;
		play_cycle(vm, cycle_to_die, dsp, times);
		del_cars(vm, cycle_to_die, 0);
		ctd_operator(vm->lives_in_cur_period, &count_cycle, &cycle_to_die, &vm->flags);
		count_cycle++;
	}
	if (cycle_to_die < 1)
	{
		vm->lives_in_cur_period = 0;
		play_cycle(vm, 1, dsp, times);
		if (vm->lives_in_cur_period)
			del_cars(vm, cycle_to_die, 1);
		ctd_operator(vm->lives_in_cur_period, &count_cycle, &cycle_to_die, &vm->flags);
	}
	del_cars(vm, cycle_to_die, 1);
	fflush(stdout);
	print_winner(vm->players, vm->winner);
	free_all(vm);
}
