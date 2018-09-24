/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vinterrupt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailkiv <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 16:39:11 by ailkiv            #+#    #+#             */
/*   Updated: 2018/09/24 17:51:38 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

void			pause_processing(t_vm *vm)
{
	char		ch;

	wattron(vm->visual->text, COLOR_PAIR(19));
	while ((ch = getch()) != 32)
	{
		if (vm->players && ch == 113)
			vm->visual->lim++;
		else if (vm->players && ch == 101)
		{
			if (vm->visual->lim > 1)
				vm->visual->lim--;
		}
		mvwprintw(vm->visual->text, 6, 2, "Cycles/second limit: %-4d",
				vm->visual->lim);
		wrefresh(vm->visual->text);
		if (ch == 115)
		{
			wattroff(vm->visual->text, COLOR_PAIR(19));
			return ;
		}
	}
	wattroff(vm->visual->text, COLOR_PAIR(19));
	vm->visual->pause = 0;
}

void			*catch_keys(void *temp)
{
	char		ch;
	t_vm		*vm;

	vm = (t_vm*)temp;
	while (vm->players && (ch = getch()) != 27)
	{
		if (vm->players == NULL)
			return (NULL);
		else if (vm->players && ch == 32)
		{
			vm->visual->pause = 1;
			return (NULL);
		}
		else if (vm->players && ch == 113)
			vm->visual->lim++;
		else if (vm->players && ch == 101)
		{
			if (vm->visual->lim > 1)
				vm->visual->lim--;
		}
	}
	return (NULL);
}

static void		renew_map(t_vm *vm)
{
	int			num;

	cycles_decrease(vm);
	num = put_car(vm);
	wattron(vm->visual->text, COLOR_PAIR(19));
	mvwprintw(vm->visual->text, 10, 13, "%-6d", num);
	mvwprintw(vm->visual->text, 8, 10, "%u", vm->game_cycle);
	mvwprintw(vm->visual->text, 6, 23, "%-4d",
			vm->visual->lim);
	renew_lives(vm);
	wattroff(vm->visual->text, COLOR_PAIR(19));
	draw_line(vm, 18);
	wrefresh(vm->visual->text);
	wrefresh(vm->visual->map);
}

void			interrupt(t_vm *vm)
{
	usleep((useconds_t)(1000000 / (1.7 * vm->visual->lim)));
	renew_map(vm);
	if (vm->visual->pause == 1)
	{
		wattron(vm->visual->text, COLOR_PAIR(19));
		mvwprintw(vm->visual->text, 4, 2, "**PAUSE**");
		wattroff(vm->visual->text, COLOR_PAIR(19));
		wrefresh(vm->visual->text);
		pause_processing(vm);
		if (vm->visual->pause == 0)
		{
			if (pthread_create(&vm->visual->keys_thread, NULL, catch_keys, vm))
			{
				endwin();
				exit(0);
			}
		}
		wattron(vm->visual->text, COLOR_PAIR(19));
		mvwprintw(vm->visual->text, 4, 2, "**PLAY** ");
		wattroff(vm->visual->text, COLOR_PAIR(19));
	}
	wrefresh(vm->visual->text);
	wrefresh(vm->visual->map);
	vm->game_cycle++;
}

void			renew_lives(t_vm *vm)
{
	t_player		*temp;
	int				i;

	i = 0;
	temp = vm->players;
	while (temp)
	{
		wattron(vm->visual->text, COLOR_PAIR(19));
		mvwprintw(vm->visual->text, 13 + i, 15,
				"%-9d", temp->last_live);
		mvwprintw(vm->visual->text, 14 + i, 29,
				"%-9d", temp->licp);
		i = i + 4;
		temp = temp->next;
		wattroff(vm->visual->text, COLOR_PAIR(19));
	}
}
