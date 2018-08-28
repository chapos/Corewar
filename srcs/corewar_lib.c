/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_lib.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 15:53:11 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/27 16:55:29 by oevtushe         ###   ########.fr       */
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

//char		ft_0x(unsigned short n)
//{
//	if (n == 10)
//		return ('a');
//	if (n == 11)
//		return ('b');
//	if (n == 12)
//		return ('c');
//	if (n == 13)
//		return ('d');
//	if (n == 14)
//		return ('e');
//	if (n == 15)
//		return ('f');
//	return (0);
//}

//void 		write_2x(char c, int i)
//{
////	unsigned short	i;
////	unsigned char	temp;
//
////	i = 0;
//	//while (i < 2)
//	if (i)
//	{
//		temp = c % 16;
//		//ft_printf("%d", temp);
//		if (temp > 9)
//		{
//			temp += 87;
//			write(1, (&temp), 1);
//		}
//		else
//		{
//			temp += 48;
//			write(1, (&temp), 1);
//		}
//		c /= 16;
//		i++;
//	}
//	write(1, " ", 1);
//}

//void 		write_2x(char c, int i)
//{
//	if (i)
//	{
//		if (c % 16 > 9)
//		{
//			write(1, ((&c %= 16) + 87), 1);
//		}
//		else
//		{
//			write(1, (&c + 48), 1);
//		}
//		write_2x(c / 16, --i);
//	}
//
//}

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
		{
//			write_2x(map[i], 2);
//			write(1, " ", 1);
			ft_printf("%.2x ", map[i]);
		}

        i++;
        if (i % 64 == 0)
            ft_printf("\n");
    }
	ft_putchar('\n');
}
