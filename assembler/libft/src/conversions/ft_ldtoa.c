/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldtoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <eyevresh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 13:47:00 by eyevresh          #+#    #+#             */
/*   Updated: 2018/02/25 13:47:00 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	fill_float_part(long value, char *res, int zero_tail)
{
	int i;

	i = 0;
	while (value)
	{
		res[i++] = (value % 10) + '0';
		value /= 10;
	}
	while (i < zero_tail)
		res[i++] = '0';
	ft_strrev(res);
	return (i);
}

static void	fill_int_part(long v, char *base, char *res, size_t *i)
{
	static int b_l;

	b_l = ft_strlen(base);
	if (v >= b_l || v <= -b_l)
		fill_int_part(v / b_l, base, res, i);
	res[(*i)++] = base[FT_ABS(v % b_l)];
}

char		*ft_ldtoa(long double value, int precision, int flag)
{
	char	*result;
	size_t	i;
	int		tmp;

	precision = precision < 0 ? 6 : precision;
	tmp = value < 0 ? 1 : 0;
	if (precision == 0)
		result = ft_strnew(ft_ilen_base((long)value, 10) + tmp + flag);
	else
		result = ft_strnew(ft_ilen_base((long)value, 10) + precision + 1 + tmp);
	if (!(i = 0) && tmp)
		result[i++] = '-';
	if (precision == 0)
		if (ft_get_float_part_long(value, 1) > 4)
			value += value < 0 ? -1.0 : 1.0;
	fill_int_part((long)value, "0123456789", result, &i);
	if (precision != 0)
	{
		result[i++] = '.';
		tmp = ft_get_rounded_float_value_long(value, precision);
		fill_float_part(tmp, result + i, precision);
	}
	if (!ft_strchr(result, '.') && flag)
		result[i] = '.';
	return (result);
}
