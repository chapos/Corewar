/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailkiv <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 16:22:24 by ailkiv            #+#    #+#             */
/*   Updated: 2018/09/22 16:27:10 by ailkiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

/*
** caret=(7,8,9,10,20)50=(15,16,17,18)diedcaret=(11,12,13,14)c50=(21,22,23,24)
*/

static void		create_colors2(void)
{
	init_color(COLOR5, 600, 1000, 600);
	init_pair(15, COLOR5, COLOR_BLACK);
	init_color(COLOR6, 600, 600, 1000);
	init_pair(16, COLOR6, COLOR_BLACK);
	init_color(COLOR7, 1000, 600, 600);
	init_pair(17, COLOR7, COLOR_BLACK);
	init_color(COLOR8, 600, 700, 1000);
	init_pair(18, COLOR8, COLOR_BLACK);
	init_color(COLOR9, 1000, 1000, 1000);
	init_pair(19, COLOR9, COLOR_BLACK);
	init_pair(11, COLOR9, COLOR1);
	init_pair(12, COLOR9, COLOR2);
	init_pair(13, COLOR9, COLOR3);
	init_pair(14, COLOR9, COLOR4);
	init_pair(21, COLOR_BLACK, COLOR5);
	init_pair(22, COLOR_BLACK, COLOR6);
	init_pair(23, COLOR_BLACK, COLOR7);
	init_pair(24, COLOR_BLACK, COLOR8);
}

void			create_colors(void)
{
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_color(COLOR_BORDER, 900, 900, 900);
	init_pair(1, COLOR_BORDER, COLOR_BORDER);
	init_color(COLOR1, 0, 700, 133);
	init_pair(3, COLOR1, COLOR_BLACK);
	init_color(COLOR2, 0, 0, 700);
	init_pair(4, COLOR2, COLOR_BLACK);
	init_color(COLOR3, 700, 0, 0);
	init_pair(5, COLOR3, COLOR_BLACK);
	init_color(COLOR4, 400, 400, 700);
	init_pair(6, COLOR4, COLOR_BLACK);
	init_pair(7, COLOR_BLACK, COLOR1);
	init_pair(8, COLOR_BLACK, COLOR2);
	init_pair(9, COLOR_BLACK, COLOR3);
	init_pair(10, COLOR_BLACK, COLOR4);
	init_color(COLOR10, 200, 200, 200);
	init_pair(20, COLOR10, COLOR10);
	init_pair(25, COLOR10, COLOR_BLACK);
	create_colors2();
}

int				on_color_caret(int cp, t_vm *vm)
{
	if (cp == COLOR_PAIR(3))
		wattron(vm->visual->map, COLOR_PAIR(7));
	else if (cp == COLOR_PAIR(4))
		wattron(vm->visual->map, COLOR_PAIR(8));
	else if (cp == COLOR_PAIR(5))
		wattron(vm->visual->map, COLOR_PAIR(9));
	else if (cp == COLOR_PAIR(6))
		wattron(vm->visual->map, COLOR_PAIR(10));
	else if (cp == COLOR_PAIR(15))
		wattron(vm->visual->map, COLOR_PAIR(21));
	else if (cp == COLOR_PAIR(16))
		wattron(vm->visual->map, COLOR_PAIR(22));
	else if (cp == COLOR_PAIR(17))
		wattron(vm->visual->map, COLOR_PAIR(23));
	else if (cp == COLOR_PAIR(18))
		wattron(vm->visual->map, COLOR_PAIR(24));
	else if (cp == COLOR_PAIR(25))
		wattron(vm->visual->map, COLOR_PAIR(20));
	else
		return (0);
	return (1);
}

void			off_color_caret(int cp, t_vm *vm)
{
	if (cp == COLOR_PAIR(3))
		wattroff(vm->visual->map, COLOR_PAIR(7));
	else if (cp == COLOR_PAIR(4))
		wattroff(vm->visual->map, COLOR_PAIR(8));
	else if (cp == COLOR_PAIR(5))
		wattroff(vm->visual->map, COLOR_PAIR(9));
	else if (cp == COLOR_PAIR(6))
		wattroff(vm->visual->map, COLOR_PAIR(10));
	else if (cp == COLOR_PAIR(15))
		wattroff(vm->visual->map, COLOR_PAIR(21));
	else if (cp == COLOR_PAIR(16))
		wattroff(vm->visual->map, COLOR_PAIR(22));
	else if (cp == COLOR_PAIR(17))
		wattroff(vm->visual->map, COLOR_PAIR(23));
	else if (cp == COLOR_PAIR(18))
		wattroff(vm->visual->map, COLOR_PAIR(24));
	else if (cp == COLOR_PAIR(25))
		wattroff(vm->visual->map, COLOR_PAIR(20));
}
