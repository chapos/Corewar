/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_address.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <eyevresh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 23:45:00 by eyevresh          #+#    #+#             */
/*   Updated: 2018/02/01 23:45:00 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char		*ft_get_address(void *address)
{
	char	*res;
	char	*conv;
	char	*tmp;

	tmp = ft_strdup("0x");
	conv = ft_ultoa_base((unsigned long)address, "0123456789abcdef");
	res = ft_strjoin(tmp, conv);
	ft_strdel(&tmp);
	ft_strdel(&conv);
	return (res);
}
