/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 09:37:45 by eyevresh          #+#    #+#             */
/*   Updated: 2018/01/15 10:44:31 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	is_base_char(char c, int str_base)
{
	if (ft_isdigit(c))
		return (1);
	else if (c >= 'A' && c <= ('A' + str_base - 10))
		return (1);
	else if (c >= 'a' && c <= ('a' + str_base - 10))
		return (1);
	else
		return (0);
}

int			ft_atoi_base(const char *str, int str_base)
{
	int result;
	int sign;

	if (str_base < 2 || str_base > 16)
		return (0);
	while (ft_iswhitespace(*str))
		str++;
	sign = *str == '-' ? -1 : 1;
	if (*str == '-' || *str == '+')
		str++;
	result = 0;
	while (is_base_char(*str, str_base))
	{
		if (*str >= 'A' && *str <= 'G')
			result = result * str_base + (*str - 'A' + 10);
		else if (*str >= 'a' && *str <= 'g')
			result = result * str_base + (*str - 'a' + 10);
		else
			result = result * str_base + (*str - '0');
		str++;
	}
	return (result * sign);
}
