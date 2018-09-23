/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_caret.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailkiv <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 16:21:52 by ailkiv            #+#    #+#             */
/*   Updated: 2018/09/22 16:21:54 by ailkiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

static void		on_color_caret_back2(int cp, t_vm *vm)
{
	if (cp == COLOR_PAIR(24))
		wattron(vm->visual->map, COLOR_PAIR(18));
	else if (cp == COLOR_PAIR(15))
		wattron(vm->visual->map, COLOR_PAIR(15));
	else if (cp == COLOR_PAIR(16))
		wattron(vm->visual->map, COLOR_PAIR(16));
	else if (cp == COLOR_PAIR(17))
		wattron(vm->visual->map, COLOR_PAIR(17));
	else if (cp == COLOR_PAIR(18))
		wattron(vm->visual->map, COLOR_PAIR(18));
	else if (cp == COLOR_PAIR(11))
		wattron(vm->visual->map, COLOR_PAIR(11));
	else if (cp == COLOR_PAIR(12))
		wattron(vm->visual->map, COLOR_PAIR(12));
	else if (cp == COLOR_PAIR(13))
		wattron(vm->visual->map, COLOR_PAIR(13));
	else if (cp == COLOR_PAIR(14))
		wattron(vm->visual->map, COLOR_PAIR(14));
	else
		wattron(vm->visual->map, COLOR_PAIR(25));
}

void			on_color_caret_back(int cp, t_vm *vm)
{
	if (cp == COLOR_PAIR(7))
		wattron(vm->visual->map, COLOR_PAIR(3));
	else if (cp == COLOR_PAIR(8))
		wattron(vm->visual->map, COLOR_PAIR(4));
	else if (cp == COLOR_PAIR(9))
		wattron(vm->visual->map, COLOR_PAIR(5));
	else if (cp == COLOR_PAIR(10))
		wattron(vm->visual->map, COLOR_PAIR(6));
	else if (cp == COLOR_PAIR(3))
		wattron(vm->visual->map, COLOR_PAIR(3));
	else if (cp == COLOR_PAIR(4))
		wattron(vm->visual->map, COLOR_PAIR(4));
	else if (cp == COLOR_PAIR(5))
		wattron(vm->visual->map, COLOR_PAIR(5));
	else if (cp == COLOR_PAIR(6))
		wattron(vm->visual->map, COLOR_PAIR(6));
	else if (cp == COLOR_PAIR(21))
		wattron(vm->visual->map, COLOR_PAIR(15));
	else if (cp == COLOR_PAIR(22))
		wattron(vm->visual->map, COLOR_PAIR(16));
	else if (cp == COLOR_PAIR(23))
		wattron(vm->visual->map, COLOR_PAIR(17));
	else
		on_color_caret_back2(cp, vm);
}

static void		off_color_caret_back2(int cp, t_vm *vm)
{
	if (cp == COLOR_PAIR(24))
		wattroff(vm->visual->map, COLOR_PAIR(18));
	else if (cp == COLOR_PAIR(15))
		wattroff(vm->visual->map, COLOR_PAIR(15));
	else if (cp == COLOR_PAIR(16))
		wattroff(vm->visual->map, COLOR_PAIR(16));
	else if (cp == COLOR_PAIR(17))
		wattroff(vm->visual->map, COLOR_PAIR(17));
	else if (cp == COLOR_PAIR(18))
		wattroff(vm->visual->map, COLOR_PAIR(17));
	else if (cp == COLOR_PAIR(11))
		wattroff(vm->visual->map, COLOR_PAIR(11));
	else if (cp == COLOR_PAIR(12))
		wattroff(vm->visual->map, COLOR_PAIR(12));
	else if (cp == COLOR_PAIR(13))
		wattroff(vm->visual->map, COLOR_PAIR(13));
	else if (cp == COLOR_PAIR(14))
		wattroff(vm->visual->map, COLOR_PAIR(14));
	else
		wattroff(vm->visual->map, COLOR_PAIR(25));
}

void			off_color_caret_back(int cp, t_vm *vm)
{
	if (cp == COLOR_PAIR(7))
		wattroff(vm->visual->map, COLOR_PAIR(3));
	else if (cp == COLOR_PAIR(8))
		wattroff(vm->visual->map, COLOR_PAIR(4));
	else if (cp == COLOR_PAIR(9))
		wattroff(vm->visual->map, COLOR_PAIR(5));
	else if (cp == COLOR_PAIR(10))
		wattroff(vm->visual->map, COLOR_PAIR(6));
	else if (cp == COLOR_PAIR(3))
		wattroff(vm->visual->map, COLOR_PAIR(3));
	else if (cp == COLOR_PAIR(4))
		wattroff(vm->visual->map, COLOR_PAIR(4));
	else if (cp == COLOR_PAIR(5))
		wattroff(vm->visual->map, COLOR_PAIR(5));
	else if (cp == COLOR_PAIR(6))
		wattroff(vm->visual->map, COLOR_PAIR(6));
	else if (cp == COLOR_PAIR(21))
		wattroff(vm->visual->map, COLOR_PAIR(15));
	else if (cp == COLOR_PAIR(22))
		wattroff(vm->visual->map, COLOR_PAIR(16));
	else if (cp == COLOR_PAIR(23))
		wattroff(vm->visual->map, COLOR_PAIR(17));
	else
		off_color_caret_back2(cp, vm);
}
