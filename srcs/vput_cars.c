/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vput_cars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailkiv <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 16:41:18 by ailkiv            #+#    #+#             */
/*   Updated: 2018/09/22 16:43:16 by ailkiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

static int		second_car(t_vm *vm, t_carriage *tcar)
{
	t_carriage		*temp;

	temp = vm->cars;
	while (temp)
	{
		if (temp->pc == tcar->pc_prev)
			return (1);
		temp = temp->next;
	}
	return (0);
}

static void		put_prev_car(t_vm *vm, t_carriage *temp)
{
	int				x;
	int				y;

	y = (temp->pc_prev) / 64 + 2;
	x = (temp->pc_prev) % 64 * 3 + 3;
	on_color_caret_back(mvwinch(vm->visual->map, y, x) & A_COLOR, vm);
	mvwprintw(vm->visual->map, y, x, "%02x", vm->map[temp->pc_prev]);
	off_color_caret_back(mvwinch(vm->visual->map, y, x) & A_COLOR, vm);
}

int				put_car(t_vm *vm)
{
	t_carriage		*temp;
	int				x;
	int				y;
	int				i;

	temp = vm->cars;
	i = 0;
	while (temp)
	{
		y = (temp->pc) / 64 + 2;
		x = (temp->pc) % 64 * 3 + 3;
		if (on_color_caret(mvwinch(vm->visual->map, y, x) & A_COLOR, vm))
		{
			mvwprintw(vm->visual->map, y, x, "%02x", vm->map[temp->pc]);
			off_color_caret(mvwinch(vm->visual->map, y, x) & A_COLOR, vm);
		}
		if (temp->pc_prev != -1 && temp->pc_prev != temp->pc &&
				!second_car(vm, temp))
			put_prev_car(vm, temp);
		temp->pc_prev = temp->pc;
		temp = temp->next;
		i++;
	}
	return (i);
}

void			vdel_car(t_vm *vm, t_carriage *tcar)
{
	int				x;
	int				y;

	y = (tcar->pc) / 64 + 2;
	x = (tcar->pc) % 64 * 3 + 3;
	if (on_color_caret(mvwinch(vm->visual->map, y, x) & A_COLOR, vm))
	{
		mvwprintw(vm->visual->map, y, x, "%02x", vm->map[tcar->pc]);
		off_color_caret(mvwinch(vm->visual->map, y, x) & A_COLOR, vm);
	}
	if (tcar->pc_prev != -1 && tcar->pc_prev != tcar->pc &&
			!second_car(vm, tcar))
		put_prev_car(vm, tcar);
	on_color_caret_back(mvwinch(vm->visual->map, y, x) & A_COLOR, vm);
	mvwprintw(vm->visual->map, y, x, "%02x", vm->map[tcar->pc]);
	off_color_caret_back(mvwinch(vm->visual->map, y, x) & A_COLOR, vm);
}
