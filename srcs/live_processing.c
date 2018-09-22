/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live_processing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailkiv <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 16:31:08 by ailkiv            #+#    #+#             */
/*   Updated: 2018/09/22 16:32:30 by ailkiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

static int		second_live(t_vm *vm)
{
	t_vcars			*temp;

	temp = vm->visual->vcars->next;
	while (temp)
	{
		if (temp->len == 4 && vm->visual->vcars->stored_to == temp->stored_to)
			return (0);
		temp = temp->next;
	}
	return (1);
}

static void		help_print_back_live(t_vm *vm, int y, int x)
{
	if (second_live(vm) && ((mvwinch(vm->visual->map, y, x) & A_COLOR) ==
				COLOR_PAIR(13)))
	{
		on_color_player(3, vm);
		mvwprintw(vm->visual->map, y, x, "%02x",
				vm->map[vm->visual->vcars->stored_to]);
		off_color_player(3, vm);
	}
	else if (second_live(vm) && ((mvwinch(vm->visual->map, y, x) & A_COLOR) ==
				COLOR_PAIR(14)))
	{
		on_color_player(4, vm);
		mvwprintw(vm->visual->map, y, x, "%02x",
				vm->map[vm->visual->vcars->stored_to]);
		off_color_player(4, vm);
	}
}

void			print_back_live(t_vm *vm)
{
	int				x;
	int				y;

	y = (vm->visual->vcars->stored_to) / 64 + 2;
	x = (vm->visual->vcars->stored_to) % 64 * 3 + 3;
	if (second_live(vm) && ((mvwinch(vm->visual->map, y, x) & A_COLOR) ==
				COLOR_PAIR(11)))
	{
		on_color_player(1, vm);
		mvwprintw(vm->visual->map, y, x, "%02x",
				vm->map[vm->visual->vcars->stored_to]);
		off_color_player(1, vm);
	}
	else if (second_live(vm) && ((mvwinch(vm->visual->map, y, x) & A_COLOR)
				== COLOR_PAIR(12)))
	{
		on_color_player(2, vm);
		mvwprintw(vm->visual->map, y, x, "%02x",
				vm->map[vm->visual->vcars->stored_to]);
		off_color_player(2, vm);
	}
	else
		help_print_back_live(vm, y, x);
}

void			live_processing(t_carriage *tcar, t_vm *vm, int len)
{
	int			x;
	int			y;
	int			i;
	int			temp;

	temp = tcar->pc;
	y = (temp) / 64 + 2;
	x = (temp) % 64 * 3 + 3;
	i = mvwinch(vm->visual->map, y, x) & A_COLOR;
	push_back_vcars(&(vm->visual->vcars), i, temp, len);
	on_color_live(i, vm);
	mvwprintw(vm->visual->map, y, x, "%02x", vm->map[temp]);
	off_color_live(i, vm);
}

void			cycle_decrease_to_end(t_vm *vm)
{
	if (vm->visual->vcars)
	{
		while (vm->visual->vcars)
		{
			if (vm->visual->vcars->len == 4)
				print_back(vm);
			else
				print_back_live(vm);
			del_front_vcars(&(vm->visual->vcars));
		}
	}
}
