/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_arr_of_pointers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 18:37:53 by eyevresh          #+#    #+#             */
/*   Updated: 2017/12/22 19:57:23 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_del_arr_of_pointers(void **table)
{
	size_t i;

	i = 0;
	while (table[i])
		free(table[i++]);
	free(table);
}
