/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uimaxlen_base.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <eyevresh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 12:16:00 by eyevresh          #+#    #+#             */
/*   Updated: 2018/01/30 12:16:00 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

size_t	ft_uimaxlen_base(uintmax_t nb, int base)
{
	size_t len;

	len = 1;
	while (nb /= base)
		len++;
	return (len);
}
