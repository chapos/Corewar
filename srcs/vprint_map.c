/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vprint_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailkiv <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 16:43:49 by ailkiv            #+#    #+#             */
/*   Updated: 2018/09/22 16:44:20 by ailkiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

static void		decide_color4(t_vm *vm, unsigned int i)
{
	if (i - 1 == MEM_SIZE / 2 + vm->players->next->next->head.prog_size)
	{
		off_color_player(3, vm);
		wattron(vm->visual->map, COLOR_PAIR(25));
	}
	if (i - 1 == 3 * MEM_SIZE / 4)
	{
		wattroff(vm->visual->map, COLOR_PAIR(25));
		on_color_player(4, vm);
	}
	if (i - 1 == 3 * MEM_SIZE / 4 +
			vm->players->next->next->next->head.prog_size)
	{
		off_color_player(4, vm);
		wattron(vm->visual->map, COLOR_PAIR(25));
	}
}

static void		decide_color3(t_vm *vm, unsigned int i, int num)
{
	if (num == 4)
	{
		if (i - 1 == MEM_SIZE / 4)
		{
			wattroff(vm->visual->map, COLOR_PAIR(25));
			on_color_player(2, vm);
		}
		if (i - 1 == MEM_SIZE / 4 + vm->players->next->head.prog_size)
		{
			off_color_player(2, vm);
			wattron(vm->visual->map, COLOR_PAIR(25));
		}
		if (i - 1 == MEM_SIZE / 2)
		{
			wattroff(vm->visual->map, COLOR_PAIR(25));
			on_color_player(3, vm);
		}
		decide_color4(vm, i);
	}
}

static void		decide_color2(t_vm *vm, unsigned int i, int num)
{
	if (num == 3)
	{
		if (i - 1 == MEM_SIZE / 3)
		{
			wattroff(vm->visual->map, COLOR_PAIR(25));
			on_color_player(2, vm);
		}
		if (i - 1 == MEM_SIZE / 3 + vm->players->next->head.prog_size)
		{
			off_color_player(2, vm);
			wattron(vm->visual->map, COLOR_PAIR(25));
		}
		if (i - 1 == 2 * MEM_SIZE / 3)
		{
			wattroff(vm->visual->map, COLOR_PAIR(25));
			on_color_player(3, vm);
		}
		if (i - 1 == 2 * MEM_SIZE / 3 + vm->players->next->next->head.prog_size)
		{
			off_color_player(3, vm);
			wattron(vm->visual->map, COLOR_PAIR(25));
		}
	}
	decide_color3(vm, i, num);
}

static void		decide_color(t_vm *vm, unsigned int i)
{
	int			num;

	num = number_of_players(vm->players);
	if (i == 1)
		on_color_player(1, vm);
	if (i - 1 == vm->players->head.prog_size)
	{
		off_color_player(1, vm);
		wattron(vm->visual->map, COLOR_PAIR(25));
	}
	if (num == 2)
	{
		if (i - 1 == MEM_SIZE / 2)
		{
			wattroff(vm->visual->map, COLOR_PAIR(25));
			on_color_player(2, vm);
		}
		if (i - 1 == MEM_SIZE / 2 + vm->players->next->head.prog_size)
		{
			off_color_player(2, vm);
			wattron(vm->visual->map, COLOR_PAIR(25));
		}
	}
	decide_color2(vm, i, num);
}

void			wprint_map(t_vm *vm)
{
	unsigned int		i;
	int					x;
	int					y;

	i = 1;
	y = 2;
	x = 3;
	while (i <= MEM_SIZE)
	{
		decide_color(vm, i);
		mvwprintw(vm->visual->map, y, x, "%02x", vm->map[i - 1]);
		if (i % 64 == 0)
		{
			x = 3;
			y++;
		}
		else
			x = x + 3;
		i++;
	}
}
