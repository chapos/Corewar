/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_front.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <eyevresh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 18:12:00 by eyevresh          #+#    #+#             */
/*   Updated: 2018/02/02 18:12:00 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strjoin_front(char *result, char *str)
{
	char	*tmp;
	size_t	size;

	size = ft_strlen(result) + ft_strlen(str);
	tmp = ft_strdup(str);
	tmp = ft_strrev(tmp);
	result = ft_strrev(result);
	result = ft_realloc(result, size + 1);
	result = ft_strcat(result, tmp);
	result = ft_strrev(result);
	ft_strdel(&tmp);
	return (result);
}
