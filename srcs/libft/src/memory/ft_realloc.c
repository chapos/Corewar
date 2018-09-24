/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 17:05:28 by eyevresh          #+#    #+#             */
/*   Updated: 2018/01/21 17:07:33 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_realloc(void *data, size_t size)
{
	void *new;

	new = ft_memalloc(size);
	ft_memcpy(new, data, ft_strlen(data));
	ft_memdel(&data);
	return (new);
}
