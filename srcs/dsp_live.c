/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dsp_live.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 17:31:19 by oevtushe          #+#    #+#             */
/*   Updated: 2018/09/08 17:05:02 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

static void	show_live(t_player *players, t_args *args, t_flags *flags)
{
	int		cnt;

	cnt = 1;
	while (players)
	{
		if (players->num_player == args->arg1.readed)
		{
			if (flags->v & 1)
			{
				printf("Player %d (%s) is said to be alive\n",
					cnt, players->head.prog_name);
			}
			return ;
		}
		players = players->next;
		cnt++;
	}
}

static void	add_live_to_player(t_player *players,
								int *winner, t_args *args, int gc)
{
	while (players)
	{
		if (players->num_player == args->arg1.readed)
		{
			*winner = players->num_player;
			players->last_live = gc;
			++players->licp;
			return ;
		}
		players = players->next;
	}
}

void		print_live(t_carriage *carriage, t_vm *vm)
{
	int			cnt;
	t_player	*players;

	cnt = 1;
	players = vm->players;
	print_pnum(carriage->num_car);
	printf("live %d\n", vm->args.arg1.readed);
	if (vm->flags.v & 1)
		show_live(vm->players, &vm->args, &vm->flags);
}

int			dsp_live(t_carriage *carriage, t_vm *vm)
{
	int pn;

	ft_memset(&vm->args, 0, sizeof(t_args));
	read_int_from_map(&pn, carriage->pc + 1, vm->map);
	vm->args.arg1.readed = pn;
	carriage->life++;
	vm->alicp++;
	carriage->last_live_cn = vm->game_cycle;
	vm->args.shift = 4;
	add_live_to_player(vm->players, &vm->winner, &vm->args, vm->game_cycle);
	if (vm->flags.v & 1 && !(vm->flags.v & 16))
		show_live(vm->players, &vm->args, &vm->flags);
	return (1);
}
