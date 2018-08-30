/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dsp_live.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 17:31:19 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/29 19:45:22 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

void		print_live(t_carriage *carriage, t_vm *vm)
{
	int			cnt;
	t_player	*players;

	cnt = 1;
	players = vm->players;
	print_pnum(carriage->num_car);
	ft_printf("live %d\n", vm->args.arg1.readed);
	while (players)
	{
		if (players->num_player == vm->args.arg1.readed)
		{
			if (vm->flags.v & 1)
			{
				write(1, "Player ", 7);
				ft_putnbr(cnt);
				write(1, " (", 2);
				ft_putstr(players->head.prog_name);
				write(1, ") is said to be alive\n", 22);
			}
			vm->winner = players->num_player;
			players->live++;
			return ;
		}
		players = players->next;
		cnt++;
	}
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
	return (1);
}
