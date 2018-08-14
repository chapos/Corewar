/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoupper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 12:43:35 by oevtushe          #+#    #+#             */
/*   Updated: 2018/03/10 10:36:52 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strtoupper(char *str)
{
	size_t i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (ft_isalpha(str[i]))
				str[i] -= ' ';
			++i;
		}
	}
}
