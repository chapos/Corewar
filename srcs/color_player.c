/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailkiv <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 16:14:03 by ailkiv            #+#    #+#             */
/*   Updated: 2018/09/22 16:14:40 by ailkiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

void			on_color_player(int num_player, t_vm *vm)
{
	if (num_player == 1)
		wattron(vm->visual->map, COLOR_PAIR(3));
	else if (num_player == 2)
		wattron(vm->visual->map, COLOR_PAIR(4));
	else if (num_player == 3)
		wattron(vm->visual->map, COLOR_PAIR(5));
	else if (num_player == 4)
		wattron(vm->visual->map, COLOR_PAIR(6));
}

void			off_color_player(int num_player, t_vm *vm)
{
	if (num_player == 1)
		wattroff(vm->visual->map, COLOR_PAIR(3));
	else if (num_player == 2)
		wattroff(vm->visual->map, COLOR_PAIR(4));
	else if (num_player == 3)
		wattroff(vm->visual->map, COLOR_PAIR(5));
	else if (num_player == 4)
		wattroff(vm->visual->map, COLOR_PAIR(6));
}

void			on_color_player_t(int num_player, t_vm *vm)
{
	if (num_player == 1)
		wattron(vm->visual->text, COLOR_PAIR(3));
	else if (num_player == 2)
		wattron(vm->visual->text, COLOR_PAIR(4));
	else if (num_player == 3)
		wattron(vm->visual->text, COLOR_PAIR(5));
	else if (num_player == 4)
		wattron(vm->visual->text, COLOR_PAIR(6));
}

void			off_color_player_t(int num_player, t_vm *vm)
{
	if (num_player == 1)
		wattroff(vm->visual->text, COLOR_PAIR(3));
	else if (num_player == 2)
		wattroff(vm->visual->text, COLOR_PAIR(4));
	else if (num_player == 3)
		wattroff(vm->visual->text, COLOR_PAIR(5));
	else if (num_player == 4)
		wattroff(vm->visual->text, COLOR_PAIR(6));
}
