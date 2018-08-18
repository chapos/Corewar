/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_byterev_ui32.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 14:28:12 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/18 14:28:27 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_byterev_ui32(unsigned int *i)
{
	*i = (*i >> 24 & 0xff) |
		(*i << 8 & 0xff0000) |
		(*i >> 8 & 0xff00) |
		(*i << 24 & 0xff000000);
}
