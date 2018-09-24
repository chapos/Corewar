/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 18:20:10 by eyevresh          #+#    #+#             */
/*   Updated: 2017/11/28 19:52:35 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t dst_length;

	dst_length = 0;
	i = 0;
	if (size > 0)
	{
		while (dst[i] != '\0' && i < size)
			i++;
		dst_length = i;
		while (src[i - dst_length] != '\0' && i < size - 1)
		{
			dst[i] = src[i - dst_length];
			i++;
		}
		if (i < size)
			dst[i] = '\0';
	}
	return (dst_length + ft_strlen(src));
}
