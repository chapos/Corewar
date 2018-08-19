/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ustoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <eyevresh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 11:44:00 by eyevresh          #+#    #+#             */
/*   Updated: 2018/01/30 11:44:00 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static void	fill(unsigned short v, char *b, char *r, size_t *i)
{
	static size_t b_l;

	b_l = ft_strlen(b);
	if (v >= b_l)
		fill(v / b_l, b, r, i);
	r[(*i)++] = b[v % b_l];
}

char		*ft_ustoa_base(unsigned short value, char *base)
{
	char	*result;
	size_t	i;
	int		base_len;

	base_len = ft_strlen(base);
	i = 0;
	if (!(result = ft_strnew(ft_uslen_base(value, base_len) + 2)))
		return (NULL);
	fill(value, base, result, &i);
	result[i] = '\0';
	return (result);
}
