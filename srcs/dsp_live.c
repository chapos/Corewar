
#include "../includes/op.h"

static int add_player_live(t_vm *vm, t_carriage *carriage)//(t_player *players, int num_player, int v)
{
	int count;
	t_player *tplayers;

	tplayers = vm->players;
	count = 1;
	if (vm->flags.v & 4)
	{
		print_pnum(carriage->num_car);
		ft_printf("live %d\n", vm->args.arg1.readed);
	}
	while (tplayers)
	{
		if (tplayers->num_player == vm->winner)
		{
			if (vm->flags.v & 1)
			{
				write(1, "Player ", 7);
				ft_putnbr(count);
				write(1, " (", 2);
				ft_putstr(tplayers->head.prog_name);
				write(1, ") is said to be alive\n", 22);
			}
			tplayers->live++;
			break ;
		}
		count++;
		tplayers = tplayers->next;
	}
	return (1);
}

void		print_live(t_carriage *carriage, t_args *args)
{
//	print_pnum(carriage->num_car);
//	ft_printf("live %d\n", args->arg1.readed);
	carriage = NULL;
	args = NULL;
}

//Player 1 (Celebration Funebre v0.99pl42) is said to be alive
//		P    1 | live 42 (WRONG ORDER)

int			dsp_live(t_carriage *carriage, t_vm *vm)
{
	int pn;

	ft_memset(&vm->args, 0, sizeof(t_args));
	read_int_from_map(&pn, carriage->pc + 1, vm->map);
	vm->args.arg1.readed = pn;
	vm->args.arg1.value = pn;
	vm->winner = pn;
	carriage->life++;
	add_player_live(vm, carriage);//->players, pn, vm->flags.v);
	carriage->last_live_cn = vm->game_cycle;
	vm->args.shift = 4;

	return (1);
}
