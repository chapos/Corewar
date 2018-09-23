/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_lib.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 15:53:11 by oevtushe          #+#    #+#             */
/*   Updated: 2018/09/23 10:56:05 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

void	free_all(t_vm *vm)
{
	t_player	*temp;

	if (vm->flags.visual && vm->visual != NULL)
		wait_end(vm);
	while (vm->players)
	{
		temp = vm->players->next;
		free(vm->players->code);
		free(vm->players);
		vm->players = temp;
	}
	exit(1);
}

void	protect_visual(t_vm *vm)
{
	vm->flags.v = 0;
	vm->flags.s = 0;
	vm->flags.d = 0;
	vm->flags.a = 0;
}

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

void	refresh_players(t_player *players)
{
	while (players)
	{
		players->licp = 0;
		players = players->next;
	}
}
