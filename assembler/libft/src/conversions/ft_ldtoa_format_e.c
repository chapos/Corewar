/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldtoa_format_e.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <eyevresh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 17:21:00 by eyevresh          #+#    #+#             */
/*   Updated: 2018/02/25 17:21:00 by eyevresh         ###   ########.fr       */
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

static int	get_exponent(long double *value, int precision)
{
	int exponent;

	exponent = 0;
	if ((long)(*value) == 0)
	{
		while ((long)(*value) == 0 && precision)
		{
			*value *= 10.0;
			precision--;
			exponent--;
		}
		exponent = (long)(*value) == 0 ? 0 : exponent;
	}
	else
	{
		while (ft_llen_base((long)(*value), 10) != 1)
		{
			*value /= 10.0;
			exponent++;
		}
	}
	return (exponent);
}

static void	handle_exponent(int exponent, char *res, size_t i, int c_case)
{
	if (c_case == 1)
		res[i++] = 'E';
	else
		res[i++] = 'e';
	if (exponent < 0)
		res[i++] = '-';
	else
		res[i++] = '+';
	if (exponent == 0)
		ft_strcat(res, "00");
	else if (FT_ABS(exponent) >= 1 && FT_ABS(exponent) <= 9)
	{
		res[i++] = '0';
		res[i] = FT_ABS(exponent) + '0';
	}
	else
	{
		res[i++] = (int)(FT_ABS(exponent) / 10) + '0';
		res[i] = FT_ABS(exponent) % 10 + '0';
	}
}

char		*ft_ldtoa_format_e(long double value, int prec, int c_case, int f)
{
	char	*result;
	size_t	i;
	int		exp;
	long	tmp;

	prec = prec < 0 ? 6 : prec;
	tmp = value < 0 ? 1 : 0;
	result = ft_strnew(prec + 1 + tmp + 5);
	if (!(i = 0) && tmp)
		result[i++] = '-';
	if (!(exp = 0) && ((long)value == 0 || ft_llen_base((long)value, 10) > 1))
		exp = get_exponent(&value, 99);
	if (prec == 0)
		if (ft_get_float_part_long(value, 1) > 4)
			value += value < 0 ? -1.0 : 1.0;
	fill_int_part((long)value, "0123456789", result, &i);
	if (prec != 0)
	{
		result[i++] = '.';
		tmp = ft_get_rounded_float_value_long(value, prec);
		i += (size_t)fill_float_part(tmp, result + i, prec);
	}
	!ft_strchr(result, '.') && f ? result[i++] = '.' : 0;
	handle_exponent(exp, result, i, c_case);
	return (result);
}
