/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_while.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 19:35:34 by oevtushe          #+#    #+#             */
/*   Updated: 2018/09/23 11:01:35 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

static void	while_tcars_helper(t_carriage *tcars, t_vm *vm, int res)
{
	if (tcars->command != 9 || (tcars->command == 9 && !res))
	{
		if (EXS_DSP(tcars->command) && vm->flags.v & 16)
			print_pc_movement(tcars->pc, vm->args.shift, vm->map);
		if (tcars->command == 1 && vm->flags.visual && vm->args.valid_live)
			live_processing(tcars, vm, 0);
		++tcars->pc;
	}
	if ((tcars->command == 3 || tcars->command == 11)
			&& vm->flags.visual && res && !vm->args.st_reg)
		command_processing(tcars, vm, 4);
}

static void	while_tcars(t_carriage *tcars, t_vm *vm, t_dsp *dsp)
{
	int res;

	res = 0;
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
			tcars->pc_prev = tcars->pc;
			while_tcars_helper(tcars, vm, res);
			tcars->pc += vm->args.shift;
			tcars->pc = normalize_pc(tcars->pc);
			tcars->command = 0;
		}
		tcars = tcars->next;
	}
}

static void	play_cycle(t_vm *vm, int cycle, t_dsp *dsp)
{
	t_carriage	*tcars;

	ft_memset(&vm->args, 0, sizeof(t_args));
	while (cycle)
	{
		if (vm->flags.visual)
			interrupt(vm);
		else
			vm->game_cycle++;
		tcars = vm->cars;
		if (vm->flags.v & 2)
			printf("It is now cycle %d\n", vm->game_cycle);
		while_tcars(tcars, vm, dsp);
		cycle--;
		if (vm->flags.d)
			flags_d(vm);
		if (vm->flags.s)
			flags_s(vm);
	}
	if (vm->flags.visual)
	{
		draw_empty_line(vm, 18);
		draw_line(vm, 21);
	}
}

static void	ctd_operator(t_vm *vm, int *count_cycle, int *ctd)
{
	if (vm->alicp >= NBR_LIVE || CHECK_MC(*count_cycle))
	{
		*ctd -= CYCLE_DELTA;
		if (vm->flags.visual)
			renew_ctd(vm, *ctd);
		if (vm->flags.v & 2)
			printf("Cycle to die is now %d\n", *ctd);
		if (vm->flags.sound)
			sound_kill_car();
		*count_cycle = 0;
	}
}

void		play_while(t_vm *vm)
{
	int			cycle_to_die;
	int			count_cycle;
	t_dsp		dsp[16];
	int			condition;

	condition = 1;
	count_cycle = 1;
	cycle_to_die = CYCLE_TO_DIE;
	init_dsp(dsp);
	vm->process_counter = vm->cars->num_car;
	if (vm->flags.visual)
		visual(vm);
	while (condition && vm->alicp)
	{
		vm->alicp = 0;
		condition = cycle_to_die > 0;
		condition ? play_cycle(vm, cycle_to_die, dsp) :
			play_cycle(vm, 1, dsp);
		del_cars(vm, cycle_to_die);
		ctd_operator(vm, &count_cycle, &cycle_to_die);
		count_cycle++;
		refresh_players(vm->players);
	}
}
