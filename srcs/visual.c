/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailkiv <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 16:32:57 by ailkiv            #+#    #+#             */
/*   Updated: 2018/09/22 16:32:59 by ailkiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

WINDOW			*create_new_win(int width, int height, int start_x, int start_y)
{
	WINDOW		*new;

	new = newwin(height, width, start_y, start_x);
	wattron(new, COLOR_PAIR(1));
	box(new, ACS_BLOCK, ACS_BLOCK);
	wattroff(new, COLOR_PAIR(1));
	wrefresh(new);
	return (new);
}

void			destroy_win(WINDOW *win)
{
	wrefresh(win);
	delwin(win);
}

static void		init_visual(t_vm *vm)
{
	if (vm->visual == NULL)
		vm->visual = (t_visual*)malloc(sizeof(t_visual));
	vm->visual->map = create_new_win(197, 68, 1, 1);
	vm->visual->text = create_new_win(60, 68, 197, 1);
	vm->visual->lim = 50;
	vm->visual->pause = 1;
	vm->visual->vcars = NULL;
}

void			visual(t_vm *vm)
{
	initscr();
	cbreak();
	noecho();
	start_color();
	curs_set(0);
	refresh();
	create_colors();
	init_visual(vm);
	wprint_map(vm);
	wprint_text(vm);
	draw_empty_line(vm, 18);
	draw_empty_line(vm, 21);
}
