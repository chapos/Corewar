/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_while.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 19:35:34 by oevtushe          #+#    #+#             */
/*   Updated: 2018/09/08 17:26:28 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

int		is_time_to_run(t_vm *vm, t_carriage *carriage)
{
	int		op;
	int		res;

	res = 0;
	op = vm->map[carriage->pc];
	if (carriage->wait > 0)
		--carriage->wait;
	else if (carriage->wait == -1 && (op >= 1 && op <= 16))
	{
		carriage->wait = vm->ops[op - 1].wait - 2;
		carriage->command = op;
	}
	else
	{
		carriage->wait = -1;
		res = 1;
	}
	return (res);
}

void while_tcars(t_carriage *tcars, t_vm *vm, t_dsp *dsp)
{
	int res;

	while (tcars)
	{
		if (is_time_to_run(vm, tcars))
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

void play_cycle(t_vm *vm, int cycle, t_dsp *dsp)
{
	t_carriage	*tcars;

	ft_memset(&vm->args, 0, sizeof(t_args));
	while (cycle)
	{
		vm->game_cycle++;
		tcars = vm->cars;
		if (vm->flags.v & 2)
			printf("It is now cycle %d\n", vm->game_cycle);
		while_tcars(tcars, vm, dsp);
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
			printf("Cycle to die is now %d\n", *ctd);
		*count_cycle = 0;
	}
}

void		refresh_players(t_player *players)
{
	while (players)
	{
		players->licp = 0;
		players = players->next;
	}
}

void		play_while(t_vm *vm)
{
	int			cycle_to_die;
	int			count_cycle;
	t_dsp		dsp[16];

	count_cycle = 1;
	cycle_to_die = CYCLE_TO_DIE;
	init_dsp(dsp);
	vm->process_counter = vm->cars->num_car;
	while (vm->alicp && cycle_to_die > 0)
	{
		vm->alicp = 0;
		play_cycle(vm, cycle_to_die, dsp);
		del_cars(vm, cycle_to_die, 0);
		ctd_operator(vm->alicp, &count_cycle, &cycle_to_die, &vm->flags);
		count_cycle++;
		refresh_players(vm->players);
	}
	if (cycle_to_die < 1 && vm->alicp)
	{
		vm->alicp = 0;
		play_cycle(vm, 1, dsp);
		//if (vm->alicp)
			del_cars(vm, cycle_to_die, 1);
		ctd_operator(vm->alicp, &count_cycle, &cycle_to_die, &vm->flags);
	}
	del_cars(vm, cycle_to_die, 1);
	fflush(stdout);
	print_winner(vm->players, vm->winner);
	free_all(vm);
}
