/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 19:46:02 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/29 19:46:04 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

void print_winner(t_player *players, int winner)
{
	int count;

	count = 1;
	while (players)
	{
		if (players->num_player == winner)
		{
			write(1, "Contestant ", 11);
			ft_putnbr(count);
			write(1, ", \"", 3);
			ft_putstr(players->head.prog_name);
			write(1, "\", has won !\n", 13);
			return ;
		}
		count++;
		players = players->next;
	}
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

void 		write_2x(char c, int i)
{
	//unsigned short	i;
	unsigned char	temp;

	i = 0;
	while (i < 2)
	{
		temp = c % 16;
		if ((temp % 16) > 9)
		{
			temp += 87;
			write(1, &temp, 1);
		}
		else
		{
			temp += 48;
			write(1, &temp, 1);
		}
		c /= 16;
		i++;
	}
	write(1, " ", 1);
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
		{
			write_2x(map[i], 2);
//			write(1, " ", 1);
			//ft_printf("%.2x ", map[i]);
		}

		i++;
		if (i % 64 == 0)
			ft_printf("\n");
	}
	ft_putchar('\n');
}
