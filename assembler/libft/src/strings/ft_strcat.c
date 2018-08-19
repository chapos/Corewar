/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 19:21:39 by eyevresh          #+#    #+#             */
/*   Updated: 2017/11/28 19:49:40 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	int s1_length;
	int j;

	j = 0;
	s1_length = ft_strlen(s1);
	while (s2[j] != '\0')
	{
		s1[s1_length] = s2[j];
		s1_length++;
		j++;
	}
	s1[s1_length] = '\0';
	return (s1);
}
