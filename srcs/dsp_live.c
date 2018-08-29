/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dsp_live.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 17:31:19 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/29 18:18:12 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

/*
static int add_player_live(t_player *players, int num_player, int v)
{
	while (players)
	{
		if (players->num_player == num_player)
		{
			if (key_validate(v, 1))
			{
				write(1, "Player ", 7);
				ft_putnbr(players->num_player);
				write(1, " (", 2);
				ft_putstr(players->head.prog_name);
				write(1, ") is said to be alive\n", 22);
			}
			players->live++;
			return (0);
		}
		players = players->next;
	}
	return (1);
}
*/

void		print_live(t_carriage *carriage, t_vm *vm)
{
	t_player *players;

	players = vm->players;
	print_pnum(carriage->num_car);
	ft_printf("live %d\n", vm->args.arg1.readed);
	while (players)
	{
		if (players->num_player == vm->args.arg1.readed)
		{
			if (key_validate(vm->flags.v, 1))
			{
				write(1, "Player ", 7);
				ft_putnbr(players->num_player);
				write(1, " (", 2);
				ft_putstr(players->head.prog_name);
				write(1, ") is said to be alive\n", 22);
			}
			players->live++;
			break ;
		}
		players = players->next;
	}
}

int			dsp_live(t_carriage *carriage, t_vm *vm)
{
	int pn;

	ft_memset(&vm->args, 0, sizeof(t_args));
	read_int_from_map(&pn, carriage->pc + 1, vm->map);
	vm->args.arg1.readed = pn;
	vm->args.arg1.value = pn;
	vm->win = pn;
	carriage->life++;
	//add_player_live(vm->players, pn, vm->flags.v);
	carriage->last_live_cn = vm->game_cycle;
	vm->args.shift = 4;
	return (1);
}
