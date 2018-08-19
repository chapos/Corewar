/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 17:12:20 by eyevresh          #+#    #+#             */
/*   Updated: 2017/11/28 19:53:30 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int		compare;
	size_t	i;

	compare = 0;
	i = 0;
	if (n == 0)
		return (0);
	while (1)
	{
		compare += (unsigned char)s1[i] - (unsigned char)s2[i];
		if ((s1[i] == '\0' && s2[i] == '\0') || (i >= n - 1))
			return (compare);
		if (s1[i] == s2[i])
			i++;
		else
			return (compare);
	}
}
