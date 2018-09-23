/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vdraw_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailkiv <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 16:40:01 by ailkiv            #+#    #+#             */
/*   Updated: 2018/09/22 16:40:50 by ailkiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

void			draw_empty_line(t_vm *vm, int coord)
{
	int			i;

	i = 0;
	mvwprintw(vm->visual->text, coord - 4 + 4 * number_of_players(vm->players),
			2, "[");
	while (i < 50)
	{
		mvwprintw(vm->visual->text, coord - 4 + 4 *
				number_of_players(vm->players), 3 + i, "-");
		i++;
	}
	mvwprintw(vm->visual->text, coord - 4 + 4 *
			number_of_players(vm->players), 3 + i, "]");
}

static int		calc_sum(t_vm *vm, int coord)
{
	int				sum;
	t_player		*temp;

	sum = 0;
	temp = vm->players;
	while (temp)
	{
		sum = sum + temp->licp;
		temp = temp->next;
	}
	if (sum == 0)
		draw_empty_line(vm, coord);
	return (sum);
}

static void		help_draw_line(t_vm *vm, int coord, t_player *temp)
{
	on_color_player_t(player_num(temp, vm), vm);
	mvwprintw(vm->visual->text, coord - 4 + 4 *
			number_of_players(vm->players), 52, "-");
	off_color_player_t(player_num(temp, vm), vm);
}

static void		help_draw_line2(t_vm *vm, int coord, t_player *temp, int i)
{
	on_color_player_t(player_num(temp, vm), vm);
	mvwprintw(vm->visual->text, coord - 4 + 4 *
			number_of_players(vm->players), 3 + i, "-");
	off_color_player_t(player_num(temp, vm), vm);
}

void			draw_line(t_vm *vm, int coord)
{
	t_player		*temp;
	int				sum;
	int				i;
	int				last_point;

	i = 0;
	last_point = 0;
	sum = calc_sum(vm, coord);
	if (sum == 0)
		return ;
	temp = vm->players;
	while (temp)
	{
		while (i < round((double)(temp->licp) / sum * 50) + last_point)
		{
			if (i >= 50 && temp->next == NULL &&
					round((double)(temp->licp) / sum * 50) != 0)
				help_draw_line(vm, coord, temp);
			if (i < 50)
				help_draw_line2(vm, coord, temp, i);
			i++;
		}
		last_point = last_point + (int)round((double)(temp->licp) / sum * 50);
		temp = temp->next;
	}
}
