/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_lib.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 15:53:11 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/25 16:16:25 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	unsigned int n;
    
    i = 0;
	n = 0;
    while (i < MEM_SIZE)
    {
        if (i % 64 == 0)
		{
			if (n == 0)
				ft_putstr("0x0000 : ");
			else
				ft_printf("%#.4x : ", n);
			n += 64;
		}
        if (color_car(cars, i))
            ft_printf("%s%.2x%s ", GREEN, map[i], RESET);
        else
            ft_printf("%.2x ", map[i]);
        i++;
        if (i % 64 == 0)
            ft_printf("\n");
    }
	ft_putchar('\n');
}
