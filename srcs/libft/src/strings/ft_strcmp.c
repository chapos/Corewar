/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 16:19:34 by eyevresh          #+#    #+#             */
/*   Updated: 2017/11/28 19:50:13 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	int compare;
	int i;

	i = 0;
	compare = 0;
	while (1)
	{
		compare += (unsigned char)s1[i] - (unsigned char)s2[i];
		if (s1[i] == '\0' && s2[i] == '\0')
			return (compare);
		if (s1[i] == s2[i])
			i++;
		else
			return (compare);
	}
}
