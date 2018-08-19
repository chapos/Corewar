/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 19:59:55 by eyevresh          #+#    #+#             */
/*   Updated: 2017/11/28 19:51:55 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int		ft_strequ(char const *s1, char const *s2)
{
	if (s1 != NULL && s2 != NULL)
	{
		if (ft_strcmp(s1, s2) == 0)
			return (1);
		else
			return (0);
	}
	return (0);
}
