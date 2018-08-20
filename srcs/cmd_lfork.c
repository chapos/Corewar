/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lfork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 11:32:06 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/20 11:32:10 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

int		cmd_lfork(t_carriage *father, unsigned char *map, t_list **root)
{
	int			npos;
	t_carriage	*son;

	son = (t_carriage *)ft_memalloc(sizeof(t_carriage));
	ft_memcpy(son, father, sizeof(t_carriage));
	read_short_from_map(&npos, father->pc + 1, map);
	son->pc = npos;
	ft_lstadd(root, ft_lstnew_cc(son, sizeof(t_carriage)));
	return (1);
}
