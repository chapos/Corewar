/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bit_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <eyevresh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 18:07:00 by eyevresh          #+#    #+#             */
/*   Updated: 2018/01/30 18:07:00 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

size_t	ft_bit_len(unsigned int value)
{
	size_t	bit_len;

	if (value == 0)
		return (0);
	bit_len = 1;
	if (value >> 16 > 0)
		bit_len += 16;
	value >>= value >> 16 > 0 ? 16 : 0;
	if (value >> 8 > 0)
		bit_len += 8;
	value >>= value >> 8 > 0 ? 8 : 0;
	if (value >> 4 > 0)
		bit_len += 4;
	value >>= value >> 4 > 0 ? 4 : 0;
	if (value >> 2 > 0)
		bit_len += 2;
	value >>= value >> 2 > 0 ? 2 : 0;
	if (value >> 1 > 0)
		bit_len += 1;
	return (bit_len);
}
