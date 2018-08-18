/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uimaxtoa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <eyevresh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 12:14:00 by eyevresh          #+#    #+#             */
/*   Updated: 2018/01/30 12:14:00 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static void	fill_result(uintmax_t v, char *b, char *r, size_t *i)
{
	static size_t b_l;

	b_l = ft_strlen(b);
	if (v >= b_l)
		fill_result(v / b_l, b, r, i);
	r[(*i)++] = b[v % b_l];
}

char		*ft_uimaxtoa_base(uintmax_t value, char *base)
{
	char	*result;
	size_t	i;
	int		base_len;

	base_len = ft_strlen(base);
	i = 0;
	if (!(result = ft_strnew(ft_uimaxlen_base(value, base_len) + 2)))
		return (NULL);
	fill_result(value, base, result, &i);
	result[i] = '\0';
	return (result);
}
