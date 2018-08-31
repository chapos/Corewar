/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dsp_live.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 17:31:19 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/30 18:00:55 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

static void		show_live(t_player *players, t_args *args, t_flags *flags)
{
	int		cnt;

	cnt = 1;
	while (players)
	{
		if (players->num_player == args->arg1.readed)
		{
			if (flags->v & 1)
			{
				//printf("Player %d (%s) is said to be alive\n", cnt, players->head.prog_name);
				write(1, "Player ", 7);
				ft_putnbr(cnt);
				write(1, " (", 2);
				ft_putstr(players->head.prog_name);
				write(1, ") is said to be alive\n", 22);
			}
			return ;
		}
		players = players->next;
		cnt++;
	}
}

static void		add_live_to_player(t_player *players, int *winner, t_args *args)
{
	while (players)
	{
		if (players->num_player == args->arg1.readed)
		{
			*winner = players->num_player;
			//players->live++;
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
	ft_printf("live %d\n", vm->args.arg1.readed);
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
	vm->lives_in_cur_period++;
	//add_player_live(vm->players, pn, vm->flags.v);
	carriage->last_live_cn = vm->game_cycle;
	vm->args.shift = 4;
	add_live_to_player(vm->players, &vm->winner, &vm->args);
	if (vm->flags.v & 1 && !(vm->flags.v & 16))
		show_live(vm->players, &vm->args, &vm->flags);
	return (1);
}
