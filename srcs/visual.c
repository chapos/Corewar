#include <ncurses.h>

void		cycle(void)
{
	
}

int			main(void)
{
	initscr();
	noecho();
	printw("hello world!");
	refresh();
	char c = getch();
	printw("%c", c);
	refresh();
	cycle();
	if (getch() == ' ')
		endwin();

	return (0);
}
