/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 17:08:46 by eyevresh          #+#    #+#             */
/*   Updated: 2017/11/28 19:49:55 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t i;

	i = 0;
	if (c == '\0')
	{
		while (1)
		{
			if (s[i] == '\0')
				return ((char*)s + i);
			i++;
		}
	}
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return ((char*)s + i);
		i++;
	}
	return (NULL);
}
