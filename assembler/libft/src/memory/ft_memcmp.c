/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 20:05:47 by eyevresh          #+#    #+#             */
/*   Updated: 2017/11/28 17:30:22 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	int		compare;

	i = 0;
	compare = 0;
	while (i < n)
	{
		compare += ((unsigned char*)s1)[i] - ((unsigned char*)s2)[i];
		if (compare != 0)
			return (compare);
		i++;
	}
	return (compare);
}
