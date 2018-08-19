/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 14:33:50 by eyevresh          #+#    #+#             */
/*   Updated: 2017/11/28 19:51:43 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	length;
	size_t	i;
	char	*copy_string;

	length = ft_strlen(s1);
	copy_string = (char*)malloc(sizeof(*copy_string) * (length + 1));
	if (!copy_string)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		copy_string[i] = s1[i];
		i++;
	}
	copy_string[i] = '\0';
	return (copy_string);
}
