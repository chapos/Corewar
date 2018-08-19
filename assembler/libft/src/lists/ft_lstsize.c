/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 15:06:13 by eyevresh          #+#    #+#             */
/*   Updated: 2017/11/28 17:29:08 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

size_t	ft_lstsize(t_list *lst)
{
	t_list *tmp;
	size_t size;

	tmp = lst;
	size = 0;
	if (tmp != NULL)
	{
		size = 1;
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
			size++;
		}
	}
	return (size);
}
