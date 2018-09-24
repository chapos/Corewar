/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_float_part.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <eyevresh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 18:33:00 by eyevresh          #+#    #+#             */
/*   Updated: 2018/02/24 18:33:00 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

long	ft_get_float_part(double value, int precision)
{
	int i;

	if (value < 0)
		value *= -1.0;
	value -= (long)value;
	i = 0;
	while (i < precision)
	{
		value *= 10.0;
		i++;
	}
	return ((long)value);
}

long	ft_get_float_part_long(long double value, int precision)
{
	int i;

	if (value < 0)
		value *= -1.0;
	value -= (long)value;
	i = 0;
	while (i < precision)
	{
		value *= 10.0;
		i++;
	}
	return ((long)value);
}
