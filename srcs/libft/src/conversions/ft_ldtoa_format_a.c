/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldtoa_format_a.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <eyevresh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 20:20:00 by eyevresh          #+#    #+#             */
/*   Updated: 2018/03/03 20:20:00 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static void	get_rounded_value(char *res, char *base, int pos)
{
	if (res[pos] - '0' > 8)
	{
		if (res[pos - 1] == 'f' || res[pos - 1] == 'F')
		{
			get_rounded_value(res, base, pos - 1);
			res[pos - 1] = '0';
		}
		else
		{
			if (res[pos - 1] - '0' == 9)
				res[pos - 1] = base[10];
			else
				res[pos - 1] += 1;
		}
	}
}

static char	*fill_floating_part(char *res, int prec, long double tmp, int c_c)
{
	char	*base;
	int		i;
	int		sign;

	sign = res[0] == '-' ? 1 : 0;
	base = c_c == 1 ? "0123456789ABCDEF" : "0123456789abcdef";
	i = ft_strlen(res);
	while (tmp *= 16)
	{
		res = ft_realloc(res, i + 2);
		res[i++] = base[(long)tmp];
		tmp -= (long)tmp;
	}
	if (prec != -1 && prec < (int)ft_strlen(res) - sign - 4)
	{
		get_rounded_value(res, base, sign + 4 + prec);
		res[sign + 4 + prec] = '\0';
	}
	else if (i - sign - 4 < prec)
	{
		res = ft_realloc(res, ft_strlen(res) + (prec - i - sign - 3));
		while (i - sign - 4 < prec)
			res[i++] = '0';
	}
	return (res);
}

static int	get_exponent(long double value)
{
	int		i;

	if (value < 0)
		value *= (-1);
	if (value < 1.0 && value > -1.0)
	{
		i = -1;
		while ((long)(value / ft_power(2, i)) != 1)
			i--;
	}
	else
	{
		i = 0;
		while ((long)(value / ft_power(2, i)) != 1)
			i++;
	}
	return (i);
}

static char	*add_exponent(char *res, int c_case, int exp)
{
	char *tmp;

	res = ft_realloc(res, ft_strlen(res) + 3 + ft_ilen_base(exp, 10));
	res = c_case == 1 ? ft_strcat(res, "P") : ft_strcat(res, "p");
	res = exp < 0 ? ft_strcat(res, "-") : ft_strcat(res, "+");
	exp *= exp < 0 ? -1 : 1;
	tmp = ft_itoa_base(exp, "0123456789");
	res = ft_strcat(res, tmp);
	ft_strdel(&tmp);
	return (res);
}

char		*ft_ldtoa_format_a(long double value, int prec, int c_case, int f)
{
	char		*res;
	long double	tmp;
	int			exponent;
	int			sign;

	if (value == 0)
		return (c_case == 1 ? ft_strdup("0X0P+0") : ft_strdup("0x0p+0"));
	sign = value < 0 ? 1 : 0;
	value *= value < 0 ? -1 : 1;
	exponent = get_exponent(value);
	res = ft_strnew(sign + 4);
	sign == 1 ? res[0] = '-' : 0;
	res = c_case == 1 ? ft_strcat(res, "0X1") : ft_strcat(res, "0x1");
	tmp = value / ft_power_long(2, exponent);
	if (prec != 0)
	{
		res[ft_strlen(res)] = '.';
		res = fill_floating_part(res, prec, tmp - (long)tmp, c_case);
		res[ft_strlen(res) - 1] == '.' ? *(ft_strchr(res, '.')) = '\0' : 0;
	}
	else
		res[sign + 2] += (long)((tmp - (long)tmp) * 16) >= 8 ? 1 : 0;
	!ft_strchr(res, '.') && f ? res[ft_strlen(res)] = '.' : 0;
	res = add_exponent(res, c_case, exponent);
	return (res);
}
