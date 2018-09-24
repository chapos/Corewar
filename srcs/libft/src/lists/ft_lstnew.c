/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 14:40:46 by eyevresh          #+#    #+#             */
/*   Updated: 2017/11/28 17:28:56 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_list	*ft_lstnew(void	const *content, size_t content_size)
{
	t_list *new_list;

	new_list = (t_list*)malloc(sizeof(*new_list));
	if (new_list == NULL)
		return (NULL);
	new_list->content = ft_memalloc(content_size);
	if (new_list->content == NULL)
	{
		free(new_list);
		return (NULL);
	}
	new_list->next = NULL;
	new_list->content_size = content_size;
	if (content == NULL)
	{
		new_list->content = NULL;
		new_list->content_size = 0;
	}
	else
		new_list->content = ft_memcpy(new_list->content, content, content_size);
	return (new_list);
}
