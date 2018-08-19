/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 17:34:21 by eyevresh          #+#    #+#             */
/*   Updated: 2017/12/22 19:41:35 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_putstr_fd(char const *s, int fd)
{
	size_t len;

	if (s != NULL)
	{
		len = ft_strlen(s);
		write(fd, s, len);
	}
}
