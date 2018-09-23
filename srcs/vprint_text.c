/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vprint_text.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailkiv <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 16:44:30 by ailkiv            #+#    #+#             */
/*   Updated: 2018/09/22 16:45:26 by ailkiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

static void		wprint_players(t_vm *vm, int *i, size_t len, t_player *temp)
{
	while (temp)
	{
		wattron(vm->visual->text, COLOR_PAIR(19));
		len = len_number(temp->num_player);
		mvwprintw(vm->visual->text, 12 + *i, 2, "Player ");
		wattroff(vm->visual->text, COLOR_PAIR(19));
		on_color_player_t(*i / 4 + 1, vm);
		mvwprintw(vm->visual->text, 12 + *i, 9, "%d", temp->num_player);
		off_color_player_t(*i / 4 + 1, vm);
		wattron(vm->visual->text, COLOR_PAIR(19));
		mvwprintw(vm->visual->text, 12 + *i, 9 + len, " : ");
		wattroff(vm->visual->text, COLOR_PAIR(19));
		on_color_player_t(*i / 4 + 1, vm);
		mvwprintw(vm->visual->text, 12 + *i, 12 + len,
				"%.40s", temp->head.prog_name);
		off_color_player_t(*i / 4 + 1, vm);
		wattron(vm->visual->text, COLOR_PAIR(19));
		mvwprintw(vm->visual->text, 13 + *i, 4, "Last live: %-6d",
				temp->last_live);
		mvwprintw(vm->visual->text, 14 + *i, 4, "Lives in current period: %-6d",
				temp->licp);
		*i = *i + 4;
		temp = temp->next;
		wattroff(vm->visual->text, COLOR_PAIR(19));
	}
}

void			wprint_text(t_vm *vm)
{
	int			i;
	size_t		len;
	t_player	*temp;

	i = 0;
	temp = vm->players;
	len = 0;
	wattron(vm->visual->text, COLOR_PAIR(19));
	mvwprintw(vm->visual->text, 4, 2, "**PLAY** ");
	mvwprintw(vm->visual->text, 6, 2, "Cycles/second limit: %-4d",
			vm->visual->lim);
	mvwprintw(vm->visual->text, 8, 2, "Cycles: %u", vm->game_cycle);
	mvwprintw(vm->visual->text, 10, 2, "Processes: %d",
			number_of_players(vm->players));
	wattroff(vm->visual->text, COLOR_PAIR(19));
	wprint_players(vm, &i, len, temp);
	wattron(vm->visual->text, COLOR_PAIR(19));
	mvwprintw(vm->visual->text, 13 + i, 2,
			"Live breakdown for current period:");
	mvwprintw(vm->visual->text, 16 + i, 2, "Live breakdown for last period:");
	mvwprintw(vm->visual->text, 20 + i, 2, "Cycle_to_Die: %d", CYCLE_TO_DIE);
	mvwprintw(vm->visual->text, 22 + i, 2, "Cycle_Delta: %d", CYCLE_DELTA);
	mvwprintw(vm->visual->text, 24 + i, 2, "NBR_Live: %d", NBR_LIVE);
	mvwprintw(vm->visual->text, 26 + i, 2, "Max_Checks: %d", MAX_CHECKS);
	wattroff(vm->visual->text, COLOR_PAIR(19));
}

void			renew_ctd(t_vm *vm, unsigned int ctd)
{
	wattron(vm->visual->text, COLOR_PAIR(19));
	mvwprintw(vm->visual->text, 20 + 4 * number_of_players(vm->players), 2,
			"Cycle_to_Die: %-4u", ctd);
	wattroff(vm->visual->text, COLOR_PAIR(19));
}

static void		printw_winner(t_vm *vm)
{
	int				count;
	t_player		*players;

	count = 1;
	players = vm->players;
	while (players)
	{
		if (players->num_player == vm->winner)
		{
			wattron(vm->visual->text, COLOR_PAIR(19));
			mvwprintw(vm->visual->text, 28 + 4 *
					number_of_players(vm->players), 2, "WINNER: ");
			wattroff(vm->visual->text, COLOR_PAIR(19));
			on_color_player_t(count, vm);
			mvwprintw(vm->visual->text, 28 + 4 * number_of_players(vm->players),
					2 + 8, "%.40s", players->head.prog_name);
			off_color_player_t(count, vm);
			return ;
		}
		count++;
		players = players->next;
	}
}

void			wait_end(t_vm *vm)
{
	int			num;

	cycle_decrease_to_end(vm);
	num = put_car(vm);
	wattron(vm->visual->text, COLOR_PAIR(19));
	mvwprintw(vm->visual->text, 10, 2, "Processes: %-6d", num);
	mvwprintw(vm->visual->text, 8, 2, "Cycles: %u", vm->game_cycle);
	mvwprintw(vm->visual->text, 6, 2, "Cycles/second limit: %-4d",
			vm->visual->lim);
	renew_lives(vm);
	wattroff(vm->visual->text, COLOR_PAIR(19));
	draw_empty_line(vm, 18);
	wattron(vm->visual->text, COLOR_PAIR(19));
	mvwprintw(vm->visual->text, 4, 2, "**FINISH** ");
	wattroff(vm->visual->text, COLOR_PAIR(19));
	printw_winner(vm);
	wrefresh(vm->visual->text);
	wrefresh(vm->visual->map);
	if (vm->visual->pause == 1)
		getch();
	pthread_join(vm->visual->keys_thread, NULL);
	destroy_win(vm->visual->map);
	destroy_win(vm->visual->text);
	endwin();
	free(vm->visual);
}
