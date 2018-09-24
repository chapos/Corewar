/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 19:17:34 by eyevresh          #+#    #+#             */
/*   Updated: 2017/11/28 17:28:43 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static void	free_lst(t_list *lst)
{
	t_list *tmp;

	while (lst != NULL)
	{
		tmp = lst->next;
		ft_memdel(&lst->content);
		free(lst);
		lst = tmp;
	}
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new_list;
	t_list *buffer;
	t_list *tmp;

	if (lst == NULL || f == NULL)
		return (NULL);
	buffer = (*f)(lst);
	new_list = ft_lstnew(buffer->content, buffer->content_size);
	if (new_list == NULL)
		return (NULL);
	tmp = new_list;
	lst = lst->next;
	while (lst != NULL)
	{
		buffer = (*f)(lst);
		new_list->next = ft_lstnew(buffer->content, buffer->content_size);
		if (new_list->next == NULL)
		{
			free_lst(tmp);
			return (NULL);
		}
		new_list = new_list->next;
		lst = lst->next;
	}
	return (tmp);
}
