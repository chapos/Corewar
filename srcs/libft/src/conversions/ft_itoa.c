/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 15:00:56 by eyevresh          #+#    #+#             */
/*   Updated: 2017/11/28 17:36:04 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_itoa(int n)
{
	char	*str;
	long	number;
	size_t	size;
	size_t	i;

	number = (long)n;
	size = ft_ilen_base(n, 10);
	str = (char*)malloc(sizeof(*str) * (size + 1));
	if (str == NULL)
		return (NULL);
	if (number < 0)
		number = -number;
	i = 1;
	str[0] = (number % 10) + '0';
	while ((number /= 10) > 0)
		str[i++] = (number % 10) + '0';
	if (n < 0)
		str[i++] = '-';
	str[i] = '\0';
	ft_strrev(str);
	return (str);
}
