/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 14:21:29 by eyevresh          #+#    #+#             */
/*   Updated: 2017/11/28 17:36:38 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

double		ft_power(double nb, int power)
{
	int		i;
	double	res;

	if (power == 0)
		return (1);
	else if (power == 1)
		return (nb);
	else if (power > 1)
	{
		res = nb;
		i = 2;
		while (i++ <= power)
			res *= nb;
	}
	else
	{
		res = 1;
		i = -1;
		while (i-- >= power)
			res /= nb;
	}
	return (res);
}

long double	ft_power_long(long double nb, int power)
{
	int			i;
	long double	res;

	if (power == 0)
		return (1);
	else if (power == 1)
		return (nb);
	else if (power > 1)
	{
		res = nb;
		i = 2;
		while (i++ <= power)
			res *= nb;
	}
	else
	{
		res = 1;
		i = -1;
		while (i-- >= power)
			res /= nb;
	}
	return (res);
}
