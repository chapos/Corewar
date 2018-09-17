#include "../includes/op.h"

#include <ncurses.h>
#include <zconf.h>
#include <pthread.h>
#include <math.h>

#define COLOR_BORDER	30
#define COLOR1			31
#define COLOR2			32
#define COLOR3			33
#define COLOR4			34
#define COLOR5			35
#define COLOR6			36
#define COLOR7			37
#define COLOR8			38
#define COLOR9			39
#define COLOR10			40

WINDOW	*create_new_win(int width, int height, int start_x, int start_y)
{
	WINDOW		*new;

	new = newwin(height, width, start_y, start_x);
	wattron(new, COLOR_PAIR(1));
	box(new, ACS_BLOCK, ACS_BLOCK);
	wattroff(new, COLOR_PAIR(1));
	wrefresh(new);
	return (new);
}

void		destroy_win(WINDOW *win)
{
//	wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
//	werase(win);
	wrefresh(win);
	delwin(win);
}

/*COLORS***********************************/

void			create_colors()
{
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_color(COLOR_BORDER, 900, 900, 900);
	init_pair(1, COLOR_BORDER, COLOR_BORDER);
	init_color(COLOR1, 0, 1000, 133);
	init_pair(3, COLOR1, COLOR_BLACK);
	init_color(COLOR2, 0, 0, 1000);
	init_pair(4, COLOR2, COLOR_BLACK);
	init_color(COLOR3, 1000, 0, 0);
	init_pair(5, COLOR3, COLOR_BLACK);
	init_color(COLOR4, 0, 900, 1000);
	init_pair(6, COLOR4, COLOR_BLACK);
	//caret color pairs
	init_pair(7, COLOR_BLACK, COLOR1);
	init_pair(8, COLOR_BLACK, COLOR2);
	init_pair(9, COLOR_BLACK, COLOR3);
	init_pair(10, COLOR_BLACK, COLOR4);
	init_color(COLOR10, 200, 200, 200);
	init_pair(20, COLOR10, COLOR10);
	//died caret color pairs
	init_pair(11, COLOR_WHITE, COLOR1);
	init_pair(12, COLOR_WHITE, COLOR2);
	init_pair(13, COLOR_WHITE, COLOR3);
	init_pair(14, COLOR_WHITE, COLOR4);
	//first 50 cycles
	init_color(COLOR5, 400, 900, 400);
	init_pair(15, COLOR5, COLOR_BLACK);
	init_color(COLOR6, 400, 400, 900);
	init_pair(16, COLOR6, COLOR_BLACK);
	init_color(COLOR7, 900, 400, 400);
	init_pair(17, COLOR7, COLOR_BLACK);
	init_color(COLOR8, 400, 900, 1000);
	init_pair(18, COLOR8, COLOR_BLACK);
	//text
	init_color(COLOR9, 1000, 1000, 1000);
	init_pair(19, COLOR9, COLOR_BLACK);
}

void			on_color_caret(int cp, t_vm *vm)
{
	if (cp == COLOR_PAIR(3))
		wattron(vm->visual->map, COLOR_PAIR(7));
	else if (cp == COLOR_PAIR(4))
		wattron(vm->visual->map, COLOR_PAIR(8));
	else if (cp == COLOR_PAIR(5))
		wattron(vm->visual->map, COLOR_PAIR(9));
	else if (cp == COLOR_PAIR(6))
		wattron(vm->visual->map, COLOR_PAIR(10));
	else if (cp == COLOR_PAIR(7))
		wattron(vm->visual->map, COLOR_PAIR(7));
	else if (cp == COLOR_PAIR(8))
		wattron(vm->visual->map, COLOR_PAIR(8));
	else if (cp == COLOR_PAIR(9))
		wattron(vm->visual->map, COLOR_PAIR(9));
	else if (cp == COLOR_PAIR(10))
		wattron(vm->visual->map, COLOR_PAIR(10));
	else
		wattron(vm->visual->map, COLOR_PAIR(20));
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
	else if (cp == COLOR_PAIR(7))
		wattroff(vm->visual->map, COLOR_PAIR(7));
	else if (cp == COLOR_PAIR(8))
		wattroff(vm->visual->map, COLOR_PAIR(8));
	else if (cp == COLOR_PAIR(9))
		wattroff(vm->visual->map, COLOR_PAIR(9));
	else if (cp == COLOR_PAIR(10))
		wattroff(vm->visual->map, COLOR_PAIR(10));
	else
		wattroff(vm->visual->map, COLOR_PAIR(20));
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
}

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

/*COLORS***********************************/



int				number_of_players(t_player *players)
{
	t_player	*temp;
	int			i;

	i = 1;
	temp = players;
	while (temp->next)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

int				player_num(t_player *player, t_vm *vm)
{
	t_player	*temp;
	int			num;

	num = 1;
	temp = vm->players;
	while (temp)
	{
		if (temp->num_player == player->num_player)
			return (num);
		num++;
		temp = temp->next;
	}
	return (0);
}

void			decide_color(t_vm *vm, unsigned int i)
{
	int			num;

	num = number_of_players(vm->players);
	if (i == 1)
		on_color_player(1, vm);
	if (i - 1 == vm->players->head.prog_size)
		off_color_player(1, vm);
	if (num == 2)
	{
		if (i - 1 == 4096 / 2)
			on_color_player(2, vm);
		if (i - 1 == 4096 / 2 + vm->players->next->head.prog_size)
			off_color_player(2, vm);
	}
	if (num == 3)
	{
		if (i - 1 == 4096 / 3)
			on_color_player(2, vm);
		if (i - 1 == 4096 / 3 + vm->players->next->head.prog_size)
			off_color_player(2, vm);
		if (i - 1 == 2 * 4096 / 3)
			on_color_player(3, vm);
		if (i - 1 == 2 * 4096 / 3 + vm->players->next->next->head.prog_size)
			off_color_player(3, vm);
	}
	if (num == 4)
	{
		if (i - 1 == 4096 / 4)
			on_color_player(2, vm);
		if (i - 1 == 4096 / 4 + vm->players->next->head.prog_size)
			off_color_player(2, vm);
		if (i - 1 == 4096 / 2)
			on_color_player(3, vm);
		if (i - 1 == 4096 / 2 + vm->players->next->next->head.prog_size)
			off_color_player(3, vm);
		if (i - 1 == 3 * 4096 / 4)
			on_color_player(4, vm);
		if (i - 1 == 3 * 4096 / 4 + vm->players->next->next->next->head.prog_size)
			off_color_player(4, vm);
	}
}

void			wprint_map(t_vm *vm)
{
	unsigned int			i;
	int			x;
	int			y;

	i = 1;
	y = 2;
	x = 3;
	while (i <= 4096)
	{
		decide_color(vm, i);
		mvwprintw(vm->visual->map, y, x, "%02x", vm->map[i - 1]);
		if (i % 64 == 0)
		{
			x = 3;
			y++;
		}
		else
			x = x + 3;
		i++;
	}
	put_car(vm);
	wrefresh(vm->visual->map);
}

size_t				len_number(int i)
{
	return (ft_strlen(ft_itoa(i)));
}

int				num_cur(t_vm *vm)
{
	t_carriage		*temp;
	int				i;

	i = 0;
	temp = vm->cars;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

void			wprint_text(t_vm *vm)
{
	t_player		*temp;
	int				i;
	size_t			len;

	i = 0;
	temp = vm->players;
	wrefresh(vm->visual->text);
	wattron(vm->visual->text, COLOR_PAIR(19));
	mvwprintw(vm->visual->text, 4, 2, "**PLAY** ");
	mvwprintw(vm->visual->text, 6, 2, "Cycles/second limit: %3d", vm->visual->lim);
	mvwprintw(vm->visual->text, 8, 2, "Cycles: %u", vm->game_cycle);
	mvwprintw(vm->visual->text, 10, 2, "Processes: %d", num_cur(vm));
	wattroff(vm->visual->text, COLOR_PAIR(19));
	while (temp)
	{
		wattron(vm->visual->text, COLOR_PAIR(19));
		len = len_number(temp->num_player);
		mvwprintw(vm->visual->text, 12 + i, 2, "Player ");
		wattroff(vm->visual->text, COLOR_PAIR(19));
		on_color_player_t(i / 4 + 1, vm);
		mvwprintw(vm->visual->text, 12 + i, 9, "%d", temp->num_player);
		off_color_player_t(i / 4 + 1, vm);
		wattron(vm->visual->text, COLOR_PAIR(19));
		mvwprintw(vm->visual->text, 12 + i, 9 + len, " : ");
		wattroff(vm->visual->text, COLOR_PAIR(19));
		on_color_player_t(i / 4 + 1, vm);
		mvwprintw(vm->visual->text, 12 + i, 12 + len, "%s", temp->head.prog_name);
		off_color_player_t(i / 4 + 1, vm);
		wattron(vm->visual->text, COLOR_PAIR(19));
		mvwprintw(vm->visual->text, 13 + i, 4, "Last live: %-6d", temp->last_live);
		mvwprintw(vm->visual->text, 14 + i, 4, "Lives in current period: %-6d", temp->licp);
		i = i + 4;
		temp = temp->next;
		wattroff(vm->visual->text, COLOR_PAIR(19));
	}
	wattron(vm->visual->text, COLOR_PAIR(19));
	mvwprintw(vm->visual->text, 13 + i, 2, "Live breakdown for current period:");
	mvwprintw(vm->visual->text, 16 + i, 2, "Live breakdown for last period:");
	mvwprintw(vm->visual->text, 20 + i, 2, "Cycle_to_Die: %d", CYCLE_TO_DIE);
	mvwprintw(vm->visual->text, 22 + i, 2, "Cycle_Delta: %d", CYCLE_DELTA);
	mvwprintw(vm->visual->text, 24 + i, 2, "NBR_Live: %d", NBR_LIVE);
	mvwprintw(vm->visual->text, 26 + i, 2, "Max_Checks: %d", MAX_CHECKS);
	wattroff(vm->visual->text, COLOR_PAIR(19));
	draw_empty_line(vm, 18);
	draw_empty_line(vm, 21);
	wrefresh(vm->visual->text);

}


/*key processing******************************/


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
		mvwprintw(vm->visual->text, 6, 2, "Cycles/second limit: %3d", vm->visual->lim);
		wrefresh(vm->visual->text);
		if (ch == 115)
		{
			wattroff(vm->visual->text, COLOR_PAIR(19));
			return;
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
			vm->visual->lim--;
	}
	return (NULL);
}

void			interrupt(t_vm *vm)
{
	usleep((useconds_t)(1000000 / vm->visual->lim));
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
	}
	wattron(vm->visual->text, COLOR_PAIR(19));
	mvwprintw(vm->visual->text, 10, 2, "Processes: %-6d", num_cur(vm));
	mvwprintw(vm->visual->text, 8, 2, "Cycles: %u", vm->game_cycle);
	mvwprintw(vm->visual->text, 4, 2, "**PLAY** ");
	mvwprintw(vm->visual->text, 6, 2, "Cycles/second limit: %-4d", vm->visual->lim);
	renew_lives(vm);
	wattroff(vm->visual->text, COLOR_PAIR(19));
	draw_line(vm, 18);
	put_car(vm);
	wrefresh(vm->visual->text);
	wrefresh(vm->visual->map);
	vm->game_cycle++;
}

/*key processing******************************/


void			init_visual(t_vm *vm)
{
	if (vm->visual == NULL)
		vm->visual = (t_visual*)malloc(sizeof(t_visual));
	vm->visual->map = create_new_win(197, 68, 1, 1);
	vm->visual->text = create_new_win(60, 68, 197, 1);
	vm->visual->lim = 100;
	vm->visual->game_cycle = 0;
	vm->visual->pause = 1;
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
}

//from abroad

void			wait_end(t_vm *vm)
{
	wattron(vm->visual->text, COLOR_PAIR(19));
	mvwprintw(vm->visual->text, 4, 2, "**FINISH** ");
	wattroff(vm->visual->text, COLOR_PAIR(19));
	wrefresh(vm->visual->text);
	pthread_join(vm->visual->keys_thread, NULL);
	if (vm->visual->pause == 1)
		getch();
	destroy_win(vm->visual->map);
	destroy_win(vm->visual->text);
	endwin();
	free(vm->visual);
}

void			renew_ctd(t_vm *vm, unsigned int ctd)
{
	wattron(vm->visual->text, COLOR_PAIR(19));
	mvwprintw(vm->visual->text, 20 + 4 * number_of_players(vm->players), 2, "Cycle_to_Die: %-4u", ctd);
	wattroff(vm->visual->text, COLOR_PAIR(19));
}

void			renew_lives(t_vm *vm)
{
	t_player *temp;
	int i;

	i = 0;
	temp = vm->players;
	while (temp)
	{
		wattron(vm->visual->text, COLOR_PAIR(19));
		mvwprintw(vm->visual->text, 13 + i, 4, "Last live: %-9d", temp->last_live);
		mvwprintw(vm->visual->text, 14 + i, 4, "Lives in current period: %-9d", temp->licp);
		i = i + 4;
		temp = temp->next;
		wattroff(vm->visual->text, COLOR_PAIR(19));
	}
}

void			draw_empty_line(t_vm *vm, int coord)
{
	int			i;

	i = 0;
	mvwprintw(vm->visual->text, coord - 4 + 4 * number_of_players(vm->players), 2, "[");
	while (i < 50)
	{
		mvwprintw(vm->visual->text, coord - 4 + 4 * number_of_players(vm->players), 3 + i, "-");
		i++;
	}
	mvwprintw(vm->visual->text, coord - 4 + 4 * number_of_players(vm->players), 3 + i, "]");
}

void			draw_line(t_vm *vm, int coord)
{
	t_player		*temp;
	int				sum;
	int				i;
	int				last_point;

	sum = 0;
	i = 0;
	last_point = 0;
	temp = vm->players;
	while (temp)
	{
		sum = sum + temp->licp;
		temp = temp->next;
	}
	if (sum == 0)
	{
		draw_empty_line(vm, coord);
		return ;
	}
	temp = vm->players;
	while (temp)
	{
		while (i < round((double)(temp->licp) / sum * 50) + last_point)
		{
			if (i >= 50 && temp->next == NULL && round((double)(temp->licp) / sum * 50) != 0)
			{
				on_color_player_t(player_num(temp, vm), vm);
				mvwprintw(vm->visual->text, coord - 4 + 4 * number_of_players(vm->players), 52, "-");
				off_color_player_t(player_num(temp, vm), vm);
			}
			if (i < 50)
			{
				on_color_player_t(player_num(temp, vm), vm);
				mvwprintw(vm->visual->text, coord - 4 + 4 * number_of_players(vm->players), 3 + i, "-");
				off_color_player_t(player_num(temp, vm), vm);
			}
			i++;
		}
		last_point = last_point + (int)round((double)(temp->licp) / sum * 50);
		temp = temp->next;
	}
}

void			put_car(t_vm *vm)
{
	t_carriage		*temp;
	int				x;
	int				y;

	temp = vm->cars;
	while (temp)
	{
		y = (temp->pc + 1) / 64 + 2;
		x = (temp->pc) % 64 * 3 + 3;
		on_color_caret(mvwinch(vm->visual->map, y, x) & A_COLOR, vm);
		mvwprintw(vm->visual->map, y, x, "%02x", vm->map[temp->pc]);
		off_color_caret(mvwinch(vm->visual->map, y, x) & A_COLOR, vm);
		if (temp->pc_prev != -1 && temp->pc_prev != temp->pc)
		{
			y = (temp->pc_prev + 1) / 64 + 2;
			x = (temp->pc_prev) % 64 * 3 + 3;
			on_color_caret_back(mvwinch(vm->visual->map, y, x) & A_COLOR, vm);
			mvwprintw(vm->visual->map, y, x, "%02x", vm->map[temp->pc_prev]);
			off_color_caret_back(mvwinch(vm->visual->map, y, x) & A_COLOR, vm);
		}
		temp->pc_prev = temp->pc;
		temp = temp->next;
	}
}

//int		main()
//{
//	t_vm	vm;
//
//	vm.visual = NULL;
//	visual(&vm, 10);
//	return (0);
//}
