/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_live.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailkiv <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 16:15:37 by ailkiv            #+#    #+#             */
/*   Updated: 2018/09/22 16:16:34 by ailkiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

void			on_color_player50(int num_player, t_vm *vm)
{
	if (num_player == 1)
		wattron(vm->visual->map, COLOR_PAIR(15));
	else if (num_player == 2)
		wattron(vm->visual->map, COLOR_PAIR(16));
	else if (num_player == 3)
		wattron(vm->visual->map, COLOR_PAIR(17));
	else if (num_player == 4)
		wattron(vm->visual->map, COLOR_PAIR(18));
}

void			off_color_player50(int num_player, t_vm *vm)
{
	if (num_player == 1)
		wattroff(vm->visual->map, COLOR_PAIR(15));
	else if (num_player == 2)
		wattroff(vm->visual->map, COLOR_PAIR(16));
	else if (num_player == 3)
		wattroff(vm->visual->map, COLOR_PAIR(17));
	else if (num_player == 4)
		wattroff(vm->visual->map, COLOR_PAIR(18));
}

void			on_color_live(int cp, t_vm *vm)
{
	if (cp == COLOR_PAIR(3) || cp == COLOR_PAIR(15) || cp == COLOR_PAIR(7)
			|| cp == COLOR_PAIR(11) || cp == COLOR_PAIR(21))
		wattron(vm->visual->map, COLOR_PAIR(11));
	else if (cp == COLOR_PAIR(4) || cp == COLOR_PAIR(16) || cp == COLOR_PAIR(8)
			|| cp == COLOR_PAIR(12) || cp == COLOR_PAIR(22))
		wattron(vm->visual->map, COLOR_PAIR(12));
	else if (cp == COLOR_PAIR(5) || cp == COLOR_PAIR(17) || cp == COLOR_PAIR(9)
			|| cp == COLOR_PAIR(13) || cp == COLOR_PAIR(23))
		wattron(vm->visual->map, COLOR_PAIR(13));
	else if (cp == COLOR_PAIR(6) || cp == COLOR_PAIR(18) || cp == COLOR_PAIR(10)
			|| cp == COLOR_PAIR(14) || cp == COLOR_PAIR(24))
		wattron(vm->visual->map, COLOR_PAIR(14));
}

void			off_color_live(int cp, t_vm *vm)
{
	if (cp == COLOR_PAIR(3) || cp == COLOR_PAIR(15) || cp == COLOR_PAIR(7)
			|| cp == COLOR_PAIR(11) || cp == COLOR_PAIR(21))
		wattroff(vm->visual->map, COLOR_PAIR(11));
	else if (cp == COLOR_PAIR(4) || cp == COLOR_PAIR(16) || cp == COLOR_PAIR(8)
			|| cp == COLOR_PAIR(12) || cp == COLOR_PAIR(22))
		wattroff(vm->visual->map, COLOR_PAIR(12));
	else if (cp == COLOR_PAIR(5) || cp == COLOR_PAIR(17) || cp == COLOR_PAIR(9)
			|| cp == COLOR_PAIR(13) || cp == COLOR_PAIR(23))
		wattroff(vm->visual->map, COLOR_PAIR(13));
	else if (cp == COLOR_PAIR(6) || cp == COLOR_PAIR(18) || cp == COLOR_PAIR(10)
			|| cp == COLOR_PAIR(14) || cp == COLOR_PAIR(24))
		wattroff(vm->visual->map, COLOR_PAIR(14));
}
