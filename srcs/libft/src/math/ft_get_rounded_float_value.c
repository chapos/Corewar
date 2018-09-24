/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_rounded_float_value.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <eyevresh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 13:36:00 by eyevresh          #+#    #+#             */
/*   Updated: 2018/02/25 13:36:00 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

long	ft_get_rounded_float_value(double value, int precision)
{
	int		i;
	long	rounded_value;

	rounded_value = ft_get_float_part(value, precision + 1);
	i = precision;
	while (i < precision + 1)
	{
		if (rounded_value % 10 > 4)
		{
			rounded_value /= 10;
			rounded_value++;
		}
		else
			rounded_value /= 10;
		i++;
	}
	return (rounded_value);
}

long	ft_get_rounded_float_value_long(long double value, int precision)
{
	int		i;
	long	rounded_value;

	rounded_value = ft_get_float_part_long(value, precision + 1);
	i = precision;
	while (i < precision + 1)
	{
		if (rounded_value % 10 > 4)
		{
			rounded_value /= 10;
			rounded_value++;
		}
		else
			rounded_value /= 10;
		i++;
	}
	return (rounded_value);
}
