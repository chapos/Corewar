/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_processing_help.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailkiv <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 16:27:35 by ailkiv            #+#    #+#             */
/*   Updated: 2018/09/22 16:30:27 by ailkiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

static void		help_print_back4(t_vm *vm, int y, int x)
{
	if (vm->visual->vcars->c_pair == COLOR_PAIR(16) &&
			((mvwinch(vm->visual->map, y, x) & A_COLOR) == COLOR_PAIR(22)))
	{
		on_color_caret(COLOR_PAIR(4), vm);
		mvwprintw(vm->visual->map, y, x, "%02x",
				vm->map[vm->visual->vcars->stored_to]);
		off_color_caret(COLOR_PAIR(4), vm);
	}
	else if (vm->visual->vcars->c_pair == COLOR_PAIR(17) &&
			((mvwinch(vm->visual->map, y, x) & A_COLOR) == COLOR_PAIR(23)))
	{
		on_color_caret(COLOR_PAIR(5), vm);
		mvwprintw(vm->visual->map, y, x, "%02x",
				vm->map[vm->visual->vcars->stored_to]);
		off_color_caret(COLOR_PAIR(5), vm);
	}
	else if (vm->visual->vcars->c_pair == COLOR_PAIR(18) &&
			((mvwinch(vm->visual->map, y, x) & A_COLOR) == COLOR_PAIR(24)))
	{
		on_color_caret(COLOR_PAIR(6), vm);
		mvwprintw(vm->visual->map, y, x, "%02x",
				vm->map[vm->visual->vcars->stored_to]);
		off_color_caret(COLOR_PAIR(6), vm);
	}
}

static void		help_print_back3(t_vm *vm, int y, int x)
{
	if (vm->visual->vcars->c_pair == COLOR_PAIR(18) &&
			((mvwinch(vm->visual->map, y, x) & A_COLOR) == COLOR_PAIR(18)))
	{
		on_color_player(4, vm);
		mvwprintw(vm->visual->map, y, x, "%02x",
				vm->map[vm->visual->vcars->stored_to]);
		off_color_player(4, vm);
	}
	else if (vm->visual->vcars->c_pair == COLOR_PAIR(15) &&
			((mvwinch(vm->visual->map, y, x) & A_COLOR) == COLOR_PAIR(21)))
	{
		on_color_caret(COLOR_PAIR(3), vm);
		mvwprintw(vm->visual->map, y, x, "%02x",
				vm->map[vm->visual->vcars->stored_to]);
		off_color_caret(COLOR_PAIR(3), vm);
	}
	else
		help_print_back4(vm, y, x);
}

void			help_print_back2(t_vm *vm, int y, int x)
{
	if (vm->visual->vcars->c_pair == COLOR_PAIR(16) &&
			((mvwinch(vm->visual->map, y, x) & A_COLOR) == COLOR_PAIR(16)))
	{
		on_color_player(2, vm);
		mvwprintw(vm->visual->map, y, x, "%02x",
				vm->map[vm->visual->vcars->stored_to]);
		off_color_player(2, vm);
	}
	else if (vm->visual->vcars->c_pair == COLOR_PAIR(17) &&
			((mvwinch(vm->visual->map, y, x) & A_COLOR) == COLOR_PAIR(17)))
	{
		on_color_player(3, vm);
		mvwprintw(vm->visual->map, y, x, "%02x",
				vm->map[vm->visual->vcars->stored_to]);
		off_color_player(3, vm);
	}
	else
		help_print_back3(vm, y, x);
}

void			help_print_back(t_vm *vm, int y, int x)
{
	if (vm->visual->vcars->c_pair == COLOR_PAIR(15) &&
			((mvwinch(vm->visual->map, y, x) & A_COLOR) == COLOR_PAIR(15)))
	{
		on_color_player(1, vm);
		mvwprintw(vm->visual->map, y, x, "%02x",
				vm->map[vm->visual->vcars->stored_to]);
		off_color_player(1, vm);
	}
	else
		help_print_back2(vm, y, x);
}

int				second_command(t_vm *vm)
{
	t_vcars			*temp;

	temp = vm->visual->vcars->next;
	while (temp)
	{
		if (temp->len == 4)
		{
			if (vm->visual->vcars->stored_to == temp->stored_to)
				return (0);
			if (vm->visual->vcars->stored_to ==
					(temp->stored_to + 1) % MEM_SIZE)
				return (0);
			if (vm->visual->vcars->stored_to ==
					(temp->stored_to + 2) % MEM_SIZE)
				return (0);
			if (vm->visual->vcars->stored_to ==
					(temp->stored_to + 3) % MEM_SIZE)
				return (0);
		}
		temp = temp->next;
	}
	return (1);
}
