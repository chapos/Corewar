/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 15:43:54 by eyevresh          #+#    #+#             */
/*   Updated: 2017/11/28 19:59:22 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <limits.h>

static int		last_check(unsigned long int val, int sign)
{
	if (val > LONG_MAX && sign > 0)
		return (-1);
	else if (val > LONG_MAX && sign < 0)
		return (0);
	else
		return (val * sign);
}

int				ft_atoi(const char *str)
{
	int					i;
	unsigned long int	res;
	int					sign;
	int					len;

	i = 0;
	sign = 1;
	res = 0;
	len = -1;
	while (str[i] == ' ' || str[i] == '\v' || str[i] == '\t' || \
			str[i] == '\n' || str[i] == '\f' || str[i] == '\r')
		++i;
	if (str[i] == '-')
	{
		sign = -1;
		++i;
	}
	else if (str[i] == '+')
		++i;
	while (str[i] == '0')
		++i;
	while (++len < 20 && ft_isdigit(str[i]))
		res = res * 10 + str[i++] - '0';
	return (last_check(res, sign));
}
