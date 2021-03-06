/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puttab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 17:00:47 by eyevresh          #+#    #+#             */
/*   Updated: 2017/12/22 19:56:07 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_puttab(char **table)
{
	size_t i;

	i = 0;
	if (table != NULL)
	{
		while (table[i] != 0)
		{
			ft_putendl(table[i]);
			i++;
		}
	}
}
