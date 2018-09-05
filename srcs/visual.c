#include <ncurses.h>
#include <zconf.h>

WINDOW	*create_new_win(int width, int height, int start_x, int start_y)
{
	WINDOW		*new;

	new = newwin(height, width, start_y, start_x);
	box(new, 0, 0);
	wrefresh(new);
	return (new);
}

void		destroy_win(WINDOW *win)
{
	wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	getch();
	werase(win);
	wrefresh(win);
	delwin(win);
}

int			main()
{
	WINDOW		*win;
	WINDOW		*temp;
	int			row;
	int			col;

	initscr();
	cbreak();
	noecho();
	refresh();
	win = create_new_win(10, 3, (COLS - 3)/2, (LINES - 10)/2);
	temp = create_new_win(50, 10, 20, 20);

	getmaxyx(win, row, col);
	wprintw(win, "lol\n");
	getmaxyx(temp, row, col);
	mvwprintw(temp, 10, 10, "kek");
	wrefresh(win);
	wrefresh(temp);
	char c = getch();
	wprintw(temp, "%c", c);
	wprintw(win, "%c", c);
	wrefresh(win);
	wrefresh(temp);
	getch();
	destroy_win(win);
	getch();
	endwin();
	return (0);
}
