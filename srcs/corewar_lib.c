
#include "../includes/op.h"

int		key_validate(int v, int value)
{
	int i;

	i = 16;
	while (v)
	{
		if (v >= i)
		{
			if (i == value)
				return (1);
			v -= i;
		}
		i /= 2;
	}
	return (0);
}

int		count_players(t_player *player)
{
	int count;

	count = 0;
	while (player)
	{
		player = player->next;
		count++;
	}
	return (count);
}

void free_all(t_vm *vm)
{
	t_player	*temp;

	del_cars(&vm->cars, vm->flags.v);
	while (vm->players)
	{
		temp = vm->players->next;
		free(vm->players->code);
		free(vm->players);
		vm->players = temp;
	}
	exit(1);
	//system("leaks corewar");
}

int color_car(t_carriage *cars, int pc)
{
	while (cars)
	{
		if (cars->pc == pc)
			return (1);
		cars = cars->next;
	}
	return (0);
}

void print_map(unsigned char *map, t_carriage *cars)
{
	unsigned int i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0)
			ft_printf("str N: %d ", (i / 64) + 1);
		if (color_car(cars, i))
		{
			ft_printf("%s%.2x%s ", RED, map[i], RESET);
		}
		else
			ft_printf("%.2x ", map[i]);
		i++;
		if (i % 64 == 0)
			ft_printf("\n");
	}
	//ft_printf("\n\n");
}