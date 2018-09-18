#include "../includes/op.h"



void			live_processing(t_carriage *tcar, t_vm *vm, int len)
{
	int 		x;
	int			y;
	int			i;
	int			temp;

	tcar = NULL;
	temp = vm->args.stored_to % MEM_SIZE;
	if (temp < 0)
		temp = temp + MEM_SIZE - 1;
	y = (temp) / 64 + 2;
	x = (temp) % 64 * 3 + 3;
	i = mvwinch(vm->visual->map, y, x) & A_COLOR;
	push_back_vcars(&(vm->visual->vcars), i, temp, len);
	on_color_live(i, vm);
	mvwprintw(vm->visual->map, y, x, "%02x", vm->map[temp]);
	off_color_live(i, vm);
	wrefresh(vm->visual->map);
}
