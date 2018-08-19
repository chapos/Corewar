/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_covnersion_functions.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <eyevresh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 16:55:00 by eyevresh          #+#    #+#             */
/*   Updated: 2018/02/24 16:55:00 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

char	*f_conversion(t_conversion *conv, va_list ap)
{
	char	*result;
	int		flag;

	flag = ft_strchr(conv->flags, '#') ? 1 : 0;
	if (ft_strequ(conv->length_modifier, "L"))
		result = ft_ldtoa(va_arg(ap, long double), conv->precision, flag);
	else
		result = ft_dtoa(va_arg(ap, double), conv->precision, flag);
	return (result);
}

char	*e_conversion(t_conversion *conv, va_list ap)
{
	char	*res;
	int		c;
	int		f;

	f = ft_strchr(conv->flags, '#') ? 1 : 0;
	c = conv->conversion_name == 'E' ? 1 : 0;
	if (ft_strequ(conv->length_modifier, "L"))
		res = ft_ldtoa_format_e(va_arg(ap, long double), conv->precision, c, f);
	else
		res = ft_dtoa_format_e(va_arg(ap, double), conv->precision, c, f);
	return (res);
}

char	*g_conversion(t_conversion *conv, va_list ap)
{
	char	*res;
	int		c;
	int		f;

	c = conv->conversion_name == 'G' ? 1 : 0;
	f = ft_strchr(conv->flags, '#') ? 1 : 0;
	if (ft_strequ(conv->length_modifier, "L"))
		res = ft_ldtoa_format_g(va_arg(ap, long double), conv->precision, c, f);
	else
		res = ft_dtoa_format_g(va_arg(ap, double), conv->precision, c, f);
	return (res);
}

char	*a_conversion(t_conversion *conv, va_list ap)
{
	char	*res;
	int		c;
	int		f;

	c = conv->conversion_name == 'A' ? 1 : 0;
	f = ft_strchr(conv->flags, '#') ? 1 : 0;
	if (ft_strequ(conv->length_modifier, "L"))
		res = ft_ldtoa_format_a(va_arg(ap, long double), conv->precision, c, f);
	else
		res = ft_dtoa_format_a(va_arg(ap, double), conv->precision, c, f);
	return (res);
}

char	*q_conversion(t_conversion *conv, va_list ap)
{
	char	*res;
	char	**tab;
	size_t	i;

	(void)conv;
	i = 1;
	tab = va_arg(ap, char **);
	res = ft_strnew(ft_strlen(tab[0]) + 1);
	res = ft_strcpy(res, tab[0]);
	res = ft_strcat(res, "\n");
	while (tab[i] != NULL)
	{
		res = ft_realloc(res, ft_strlen(res) + ft_strlen(tab[i]) + 1);
		res = ft_strcat(res, tab[i]);
		res = ft_strcat(res, "\n");
		i++;
	}
	return (res);
}
