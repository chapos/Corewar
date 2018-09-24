/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 16:23:24 by eyevresh          #+#    #+#             */
/*   Updated: 2017/11/28 19:53:18 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t s1_length;
	size_t j;

	j = 0;
	s1_length = ft_strlen(s1);
	while (s2[j] != '\0' && j < n)
	{
		s1[s1_length] = s2[j];
		s1_length++;
		j++;
	}
	s1[s1_length] = '\0';
	return (s1);
}
