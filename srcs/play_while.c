/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_while.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 19:35:34 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/20 19:55:46 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

int		check_live()
{

}

int play_cycle(t_vm *vm)
{
	// player number
	int			pn;
	t_carriage	*tcars;
	int				(*dsp[16])(t_carriage*, unsigned char*);

	while (cycle)
	{
		tcars = vm->cars;

		while (tcars)
		{
			if (vm->map[tcars->pc] - 1 > 1 && vm->map[tcars->pc] - 1 < 16 &&
					dsp[vm->map[tcars->pc] - 1])
			{
				dsp[vm->map[tcars->pc] - 1](tcars, map);
			}
			else if (vm->map[tcars] == 1)
			{
				// live
				cmd_live(tcars, vm->map, &pn);
				read_int_from_map(&pn, tcars->pc + 1, vm->map);
				// increase live counter for player with 'pn' number
			}
			else if (vm->map[tcars] == 12)
			{
				// fork
				// pass pointer at pointer at the begining of the list of carriages
				// instead of HERE
				cmd_fork(tcars, map, HERE);
			}
			else if (vm->map[tcars] == 15)
			{
				// lfork
				// the same as with fork
				cmd_lfork(tcars, map, HERE);
			}
		}

		cycle--;
	}
}

int play_while(t_vm *vm)
{
	int 		cycle;
	int 		cycle_to_die;
	int 		count_cycle;
	int 		count_live;

	count_cycle = 0;
	cycle_to_die = CYCLE_TO_DIE;

	while ((count_live = check_live(vm->players)))
	{
		cycle = cycle_to_die;
		if (count_cycle == MAX_CHECKS || count_live > NBR_LIVE)
			cycle_to_die /= CYCLE_DELTA;

		play_cycle(vm);
//		while (cycle)
//		{
//			cycle--;
//		}
		count_cycle++;
	}
}

int play_start(t_vm *vm)
{

}
