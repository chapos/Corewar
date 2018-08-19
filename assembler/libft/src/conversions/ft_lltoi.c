/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <eyevresh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 16:06:00 by eyevresh          #+#    #+#             */
/*   Updated: 2018/03/06 16:06:00 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

long long	ft_lltoi(const char *str)
{
	int			sign;
	long long	result;

	result = 0;
	sign = 1;
	while (ft_iswhitespace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		sign = (*str == '-') ? -1 : 1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		result = (result * 10) + (*str - '0');
		str++;
	}
	return (result * sign);
}
