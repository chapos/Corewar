/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa_format_g.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <eyevresh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 15:22:00 by eyevresh          #+#    #+#             */
/*   Updated: 2018/03/02 15:22:00 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static void	remove_trailing_zeroes(char *result, int c_case)
{
	char	tmp[5];
	size_t	i;

	if (c_case)
		ft_strcpy(tmp, ft_strchr(result, 'E'));
	else
		ft_strcpy(tmp, ft_strchr(result, 'e'));
	i = ft_strlen(result) - 5;
	if (ft_strchr(result, '.'))
	{
		if (result[i] == '0')
		{
			while (result[i] == '0')
				i--;
			result[i] == '.' ? result[i] = '\0' : i++;
			result[i] = '\0';
			ft_strcat(result, tmp);
		}
	}
}

static int	get_format(double value, int precision)
{
	int format;
	int exponent;
	int counter;

	exponent = 0;
	format = 0;
	counter = 0;
	if ((long)value == 0)
	{
		while ((long)value == 0 && counter < 99)
		{
			value *= 10.0;
			counter++;
			exponent--;
		}
		if ((long)value != 0)
			format = exponent < -4 ? 1 : 0;
	}
	else if (ft_llen_base((long)value, 10) > 1
			&& (int)ft_llen_base((long)value, 10) - 1 >= precision)
		format = 1;
	return (format);
}

static char	*handle_f_format(double value, int precision, int f)
{
	int		sign;
	long	float_part;
	char	*result;

	sign = value < 0 ? 1 : 0;
	precision -= (long)value == 0 ? -3 : ft_llen_base((long)value, 10);
	if ((long)value == 0)
	{
		float_part = ft_get_float_part(value, precision);
		if ((int)ft_llen_base(float_part, 10) > precision - 3)
			precision -= ft_llen_base(float_part, 10) - (precision - 3);
	}
	precision -= value == 0 && f ? 4 : 0;
	result = ft_dtoa(value, precision, f);
	while (!f && result[ft_strlen(result) - 1] == '0' && precision)
	{
		result[ft_strlen(result) - 1] = '\0';
		precision--;
	}
	if (!f && ft_strlen(result) == ft_llen_base((long)value, 10) + 1 + sign)
		result[ft_strlen(result) - 1] = '\0';
	return (result);
}

char		*ft_dtoa_format_g(double value, int precision, int c_case, int f)
{
	char	*result;

	precision = precision < 0 ? 6 : precision;
	precision = precision == 0 ? 1 : precision;
	if (get_format(value, precision))
	{
		result = ft_dtoa_format_e(value, precision - 1, c_case, f);
		if (!f)
			remove_trailing_zeroes(result, c_case);
	}
	else
		result = handle_f_format(value, precision, f);
	return (result);
}
