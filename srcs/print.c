/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 19:46:02 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/30 15:10:05 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

void		print_winner(t_player *players, int winner)
{
	int				count;

	count = 1;
	while (players)
	{
		if (players->num_player == winner)
		{
			fflush(stdout);
			ft_printf("Contestant %d, \"%s\","
							" has won !\n", count, players->head.prog_name);
			return ;
		}
		count++;
		players = players->next;
	}
}

static int	color_car(t_carriage *cars, int pc)
{
	while (cars)
	{
		if (cars->pc == pc)
			return (1);
		cars = cars->next;
	}
	return (0);
}

void		print_map(unsigned char *map, t_carriage *cars)
{
	unsigned int	i;
	unsigned int	n;

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
			ft_putchar('\n');
	}
	ft_putchar('\n');
}
