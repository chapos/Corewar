
#include "../includes/op.h"

static int add_player_live(t_player *players, int num_player, int v)
{
	while (players)
	{
		if (players->num_player == num_player)
		{
			if (key_validate(v, 1))
			{
				write(1, "Player ", 7);
				ft_putnbr(players->num_player);
				write(1, "(", 1);
				ft_putstr(players->head.prog_name);
				write(1, ") is said to be alive\n", 22);

//				ft_printf("Player %d ", players->num_player);
//				ft_printf("(%s) is said to be alive\n", players->head.prog_name);
			}
			players->live++;
			return (0);
		}
		players = players->next;
	}
	return (1);
}

void		print_live(t_carriage *carriage, t_args *args)
{
	print_pnum(carriage->num_car);
	ft_printf("live %d\n", args->arg1.readed);
}

int			dsp_live(t_carriage *carriage, t_vm *vm)
{
	int pn;

	ft_memset(&vm->args, 0, sizeof(t_args));
	read_int_from_map(&pn, carriage->pc + 1, vm->map);
	vm->args.arg1.readed = pn;
	vm->args.arg1.value = pn;
	vm->win = pn;
	carriage->life++;
	add_player_live(vm->players, carriage->num_player, vm->flags.v);
	carriage->last_live_cn = vm->game_cycle;
	vm->args.shift = 4;
	return (1);
}
