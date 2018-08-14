/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpetluk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 12:22:51 by rpetluk           #+#    #+#             */
/*   Updated: 2018/08/14 12:30:34 by rpetluk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{

	unsigned char		map[MEM_SIZE];
	t_list	*players;
	players = NULL;

	unsigned int i;

	i = 0;

	read_players(&players, argc, argv);
	write_in_map(map, players);
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0)
			printf("str N: %d ", (i / 64) + 1);
		printf("%.2x ", map[i]);
		i++;
		if (i % 64 == 0)
			printf("\n");
	}





	return (0);
}
