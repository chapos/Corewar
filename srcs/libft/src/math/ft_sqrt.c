/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 14:31:55 by eyevresh          #+#    #+#             */
/*   Updated: 2017/11/28 17:36:58 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int		ft_sqrt(int nb)
{
	int sqrt;
	int result;

	sqrt = 0;
	result = 0;
	while (sqrt < nb / 2)
	{
		result = sqrt * sqrt;
		if (result == nb)
			return (sqrt);
		sqrt++;
	}
	return (0);
}
