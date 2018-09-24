/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <eyevresh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 16:18:00 by eyevresh          #+#    #+#             */
/*   Updated: 2018/01/29 16:18:00 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static void	fill_result_str(short v, char *base, char *res, size_t *i)
{
	static int b_l;

	b_l = (int)ft_strlen(base);
	if (v >= b_l || v <= -b_l)
		fill_result_str(v / b_l, base, res, i);
	res[(*i)++] = base[FT_ABS(v % b_l)];
}

char		*ft_stoa_base(short value, char *base)
{
	char	*result;
	size_t	i;
	int		base_len;

	base_len = ft_strlen(base);
	i = 0;
	if (!(result = ft_strnew(ft_slen_base(value, base_len) + 2)))
		return (NULL);
	if (base_len == 10 && value < 0)
		result[i++] = '-';
	fill_result_str(value, base, result, &i);
	result[i] = '\0';
	return (result);
}
