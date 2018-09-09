
#include "../includes/op.h"

int sound_kill_car(void)
{
	if (system("afplay pp.mp3"))
		exit(100);
	return (0);
}

void	flags_s(t_vm *vm)
{
	char	c;

	if (vm->game_cycle % vm->flags.s == 0)
	{
		print_map(vm->map);
		read(1, &c, 1);
	}
}

void	flags_d(t_vm *vm)
{
	if (vm->flags.d == vm->game_cycle)
	{
		print_map(vm->map);
		free_all(vm);
	}
}