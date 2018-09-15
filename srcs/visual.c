#include "../includes/op.h"

#include <ncurses.h>
#include <zconf.h>
#include <pthread.h>

#define COLOR_BORDER	20
#define COLOR1			21
#define COLOR2			22
#define COLOR3			23
#define COLOR4			24
#define COLOR5			25
#define COLOR6			26
#define COLOR7			27
#define COLOR8			28
#define COLOR9			29

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

void			on_color_caret(int num_player, t_vm *vm, int died)
{
	if (died == 0)
	{
		if (num_player == 1)
			wattron(vm->visual->map, COLOR_PAIR(7));
		else if (num_player == 2)
			wattron(vm->visual->map, COLOR_PAIR(8));
		else if (num_player == 3)
			wattron(vm->visual->map, COLOR_PAIR(9));
		else if (num_player == 4)
			wattron(vm->visual->map, COLOR_PAIR(10));
	}
	else
	{
		if (num_player == 1)
			wattron(vm->visual->map, COLOR_PAIR(11));
		else if (num_player == 2)
			wattron(vm->visual->map, COLOR_PAIR(12));
		else if (num_player == 3)
			wattron(vm->visual->map, COLOR_PAIR(13));
		else if (num_player == 4)
			wattron(vm->visual->map, COLOR_PAIR(14));
	}
}

void			off_color_caret(int num_player, t_vm *vm, int died)
{
	if (died == 0)
	{
		if (num_player == 1)
			wattroff(vm->visual->map, COLOR_PAIR(7));
		else if (num_player == 2)
			wattroff(vm->visual->map, COLOR_PAIR(8));
		else if (num_player == 3)
			wattroff(vm->visual->map, COLOR_PAIR(9));
		else if (num_player == 4)
			wattroff(vm->visual->map, COLOR_PAIR(10));
	}
	else
	{
		if (num_player == 1)
			wattroff(vm->visual->map, COLOR_PAIR(11));
		else if (num_player == 2)
			wattroff(vm->visual->map, COLOR_PAIR(12));
		else if (num_player == 3)
			wattroff(vm->visual->map, COLOR_PAIR(13));
		else if (num_player == 4)
			wattroff(vm->visual->map, COLOR_PAIR(14));
	}
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
	wrefresh(vm->visual->map);
}

size_t				len_number(int i)
{
	return (ft_strlen(ft_itoa(i)));
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
	mvwprintw(vm->visual->text, 10, 2, "Processes: ***");
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
		mvwprintw(vm->visual->text, 13 + i, 4, "Last live: ***");
		mvwprintw(vm->visual->text, 14 + i, 4, "Lives in current period: ***");
		i = i + 4;
		temp = temp->next;
		wattroff(vm->visual->text, COLOR_PAIR(19));
	}
	wattron(vm->visual->text, COLOR_PAIR(19));
	mvwprintw(vm->visual->text, 22 + i, 2, "Cycle_to_Die: %d", CYCLE_TO_DIE);
	mvwprintw(vm->visual->text, 24 + i, 2, "Cycle_Delta: %d", CYCLE_DELTA);
	mvwprintw(vm->visual->text, 26 + i, 2, "NBR_Live: %d", NBR_LIVE);
	mvwprintw(vm->visual->text, 28 + i, 2, "Max_Checks: %d", MAX_CHECKS);
	wattroff(vm->visual->text, COLOR_PAIR(19));
	wrefresh(vm->visual->text);

}

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
		if (vm->players && ch == 32)
		{
			vm->visual->pause = 1;
			return (NULL);
		}
		else if (vm->players && ch == 113)
			vm->visual->lim++;
		else if (vm->players && ch == 101)
			vm->visual->lim--;
		else if (vm->players == NULL)
			return (NULL);
	}
	if (vm->players == NULL)
		return (NULL);
	endwin();
	exit(0);
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
	vm->game_cycle++;
	wattron(vm->visual->text, COLOR_PAIR(19));
	mvwprintw(vm->visual->text, 8, 2, "Cycles: %u", vm->game_cycle);
	mvwprintw(vm->visual->text, 4, 2, "**PLAY**");
	mvwprintw(vm->visual->text, 6, 2, "Cycles/second limit: %3d", vm->visual->lim);
	wattroff(vm->visual->text, COLOR_PAIR(19));
	wrefresh(vm->visual->text);
	wrefresh(vm->visual->map);
}

void			init_visual(t_vm *vm)
{
	if (vm->visual == NULL)
		vm->visual = (t_visual*)malloc(sizeof(t_visual));
	vm->visual->map = create_new_win(197, 68, 1, 1);
	vm->visual->text = create_new_win(60, 68, 197, 1);
	vm->visual->lim = 50;
	vm->visual->game_cycle = 0;
	vm->visual->pause = 1;
}

void			visual(t_vm *vm, int cycle_to_die)
{

	initscr();
	cbreak();
	noecho();
	start_color();
	curs_set(0);
//	nodelay(stdscr, TRUE);
	refresh();
	cycle_to_die = 0;
	create_colors();
	init_visual(vm);
	wprint_map(vm);
	wprint_text(vm);
}

void			wait_end(t_vm *vm)
{
	getch();
	destroy_win(vm->visual->map);
	destroy_win(vm->visual->text);
	endwin();
	pthread_join(vm->visual->keys_thread, NULL);
	free(vm->visual);
}

//int		main()
//{
//	t_vm	vm;
//
//	vm.visual = NULL;
//	visual(&vm, 10);
//	return (0);
//}
