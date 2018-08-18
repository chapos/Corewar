/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 15:23:59 by eyevresh          #+#    #+#             */
/*   Updated: 2017/11/28 19:54:35 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strrev(char *str)
{
	size_t	len;
	size_t	i;
	char	tmp;

	i = 0;
	len = 0;
	while (str[len] != '\0')
		len++;
	while (i < len / 2)
	{
		tmp = str[len - (i + 1)];
		str[len - (i + 1)] = str[i];
		str[i] = tmp;
		i++;
	}
	return (str);
}
