/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_while.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 19:35:34 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/23 15:42:46 by oevtushe         ###   ########.fr       */
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

//int play_cycle(t_vm *vm, int cycle)
//{
//	int			pn;
//	t_carriage	*tcars;
//	int			(*dsp[16])(t_carriage*, unsigned char*);
//	int			times[16];
//	int			ncycle;
//
//	ncycle = 1;
//	init_dsp(dsp);
//	init_times(times);
//	while (cycle)
//	{
//		tcars = vm->cars;
//		while (tcars)
//		{
//			if (is_time_to_run(vm->map[tcars->pc], tcars, times))
//			{
//
//				if (vm->map[tcars->pc] - 1 > 0 && vm->map[tcars->pc] - 1 < 16 &&
//						dsp[vm->map[tcars->pc] - 1])
//					dsp[vm->map[tcars->pc] - 1](tcars, vm->map);
//				else if (vm->map[tcars->pc] == 1)
//				{
//					read_int_from_map(&pn, tcars->pc + 1, vm->map);
//					ft_printf("pn = %d\n", pn);
//					add_player_live(vm->players, pn);
//					tcars->pc += 5;
//					tcars->pc %= MEM_SIZE;
//				}
//				else if (vm->map[tcars->pc] == 12)
//					cmd_fork(tcars, vm->map, &vm->cars);
//				else if (vm->map[tcars->pc] == 15)
//					cmd_lfork(tcars, vm->map, &vm->cars);
//				else
//				{
//					++tcars->pc;
//					tcars->pc %= MEM_SIZE;
//				}
//
//			}
//
////			ft_printf("Carry: %d\n", tcars->carry);
//			tcars = tcars->next;
//		}
//		cycle--;
//		//ft_printf("Is now cycle: %d\n", ncycle++);
//		//print_map(vm->map, vm->cars);
////		char c;
////		read(1, &c, 1);
//	}
//	return (0);
//}

//int play_while(t_vm *vm)
//{
//	int 		cycle;
//	int 		cycle_to_die;
//	int 		count_cycle;
//	int 		count_live;
//
//	count_cycle = 0;
//	cycle_to_die = CYCLE_TO_DIE;
//
//	while ((count_live = check_live(&vm->players, &vm->cars)) && cycle_to_die > 0)
//	{
//		cycle = cycle_to_die;
//		if (count_cycle == MAX_CHECKS || count_live > NBR_LIVE)
//			cycle_to_die /= CYCLE_DELTA;
//		play_cycle(vm, cycle);
//		count_cycle++;
//		//print_map(vm->map, vm->cars);
//		//ft_printf("%d\n", count_cycle);
//	}
//	return (0);
//}

int play_cycle(t_vm *vm, int cycle, t_visual *visual, t_ama_dispatcher *dsp)
{
	int			pn;
	t_carriage	*tcars;
	int			times[16];
	int			ncycle;
	int			live;

	live = 0;
	ncycle = 1;
	init_times(times);
	while (cycle)
	{
		tcars = vm->cars;
		while (tcars)
		{
			if (is_time_to_run(vm->map[tcars->pc], tcars, times))
			{

				if (vm->map[tcars->pc] - 1 > 0 && vm->map[tcars->pc] - 1 < 16 &&
						dsp[vm->map[tcars->pc] - 1].exec_cmd)
				{
					dsp[vm->map[tcars->pc] - 1].exec_cmd(tcars, vm->map, visual);
					dsp[visual->op - 1].print_cmd(tcars, visual);
				}
				else if (vm->map[tcars->pc] == 1)
				{
					read_int_from_map(&pn, tcars->pc + 1, vm->map);
					ft_printf("pn = %d\n", pn);
					if (add_player_live(vm->players, pn))
						live++;
					tcars->pc += 5;
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

//			ft_printf("Carry: %d\n", tcars->carry);
			tcars = tcars->next;
		}
		if (vm->flags.d && ncycle == vm->flags.d)
		{
			ft_printf("Is now cycle: %d\n", ncycle++);
			print_map(vm->map, vm->cars);
			char c;
			read(1, &c, 1);
		}
		cycle--;
		ncycle++;
	}
	return (live);
}

void	init_visual(t_visual *visual)
{
	visual->op_names[0] = ft_strdup("live");
	visual->op_names[1] = ft_strdup("ld");
	visual->op_names[2] = ft_strdup("st");
	visual->op_names[3] = ft_strdup("add");
	visual->op_names[4] = ft_strdup("sub");
	visual->op_names[5] = ft_strdup("and");
	visual->op_names[6] = ft_strdup("or");
	visual->op_names[7] = ft_strdup("xor");
	visual->op_names[8] = ft_strdup("zjmp");
	visual->op_names[9] = ft_strdup("ldi");
	visual->op_names[10] = ft_strdup("sti");
	visual->op_names[11] = ft_strdup("fork");
	visual->op_names[12] = ft_strdup("lld");
	visual->op_names[13] = ft_strdup("lldi");
	visual->op_names[14] = ft_strdup("lfork");
	visual->op_names[15] = ft_strdup("aff");
}

int play_while(t_vm *vm)
{
	int 		cycle;
	int 		cycle_to_die;
	int 		count_cycle;
	int 		count_live;
	int			live;
	t_visual	visual;
	t_ama_dispatcher dsp[16];

	live = 0;
	count_cycle = 1;
	cycle_to_die = CYCLE_TO_DIE;
	ft_memset(&visual, 0, sizeof(t_visual));
	init_visual(&visual);
	init_dsp(dsp);

	while (live || (count_live = check_live(&vm->players, &vm->cars)))
	{
		if (cycle_to_die < 1)
			free_all(vm);
		cycle = cycle_to_die;
		if (count_cycle % MAX_CHECKS == 0 || count_live > NBR_LIVE)
			cycle_to_die /= CYCLE_DELTA;
		live = play_cycle(vm, cycle, &visual, dsp);
		count_cycle++;
		//print_map(vm->map, vm->cars);
		//ft_printf("%d\n", count_cycle);
	}
	while (vm->cars)
		vm->cars = vm->cars->next;
	return (0);
}
