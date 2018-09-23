/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vplayer_num.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailkiv <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 16:37:18 by ailkiv            #+#    #+#             */
/*   Updated: 2018/09/22 16:37:20 by ailkiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

int				number_of_players(t_player *players)
{
	t_player	*temp;
	int			i;

	i = 1;
	temp = players;
	while (temp->next)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

int				player_num(t_player *player, t_vm *vm)
{
	t_player	*temp;
	int			num;

	num = 1;
	temp = vm->players;
	while (temp)
	{
		if (temp->num_player == player->num_player)
			return (num);
		num++;
		temp = temp->next;
	}
	return (0);
}

size_t			len_number(int i)
{
	char		*temp;
	size_t		len;

	temp = ft_itoa(i);
	len = ft_strlen(temp);
	free(temp);
	return (len);
}
