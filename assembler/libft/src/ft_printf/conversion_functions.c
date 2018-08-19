/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <eyevresh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 17:39:00 by eyevresh          #+#    #+#             */
/*   Updated: 2018/01/21 17:39:00 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

char	*di_conversion(t_conversion *conv, va_list ap)
{
	char	*res;

	if (ft_strequ(conv->length_modifier, "h"))
		res = ft_stoa_base((short)va_arg(ap, int), "0123456789");
	else if (ft_strequ(conv->length_modifier, "hh"))
		res = ft_ctoa_base((char)va_arg(ap, int), "0123456789");
	else if (ft_strequ(conv->length_modifier, "l"))
		res = ft_ltoa_base(va_arg(ap, long), "0123456789");
	else if (ft_strequ(conv->length_modifier, "ll"))
		res = ft_lltoa_base(va_arg(ap, long long), "0123456789");
	else if (ft_strequ(conv->length_modifier, "j"))
		res = ft_imaxtoa_base(va_arg(ap, intmax_t), "0123456789");
	else if (ft_strequ(conv->length_modifier, "z"))
		res = ft_ssizetoa_base(va_arg(ap, ssize_t), "0123456789");
	else
		res = ft_itoa_base(va_arg(ap, int), "0123456789");
	return (res);
}

char	*ouxb_conversion(t_conversion *conv, va_list ap)
{
	char	*res;
	char	*base;

	base = get_base_for_conv(conv->conversion_name);
	if (ft_strequ(conv->length_modifier, "h"))
		res = ft_ustoa_base((unsigned short)va_arg(ap, int), base);
	else if (ft_strequ(conv->length_modifier, "hh"))
		res = ft_uctoa_base((unsigned char)va_arg(ap, int), base);
	else if (ft_strequ(conv->length_modifier, "l"))
		res = ft_ultoa_base(va_arg(ap, unsigned long), base);
	else if (ft_strequ(conv->length_modifier, "ll"))
		res = ft_ulltoa_base(va_arg(ap, unsigned long long), base);
	else if (ft_strequ(conv->length_modifier, "j"))
		res = ft_uimaxtoa_base(va_arg(ap, uintmax_t), base);
	else if (ft_strequ(conv->length_modifier, "z"))
		res = ft_sizetoa_base(va_arg(ap, size_t), base);
	else
		res = ft_uitoa_base(va_arg(ap, unsigned int), base);
	return (res);
}

char	*c_conversion(t_conversion *conv, va_list ap)
{
	unsigned char	*res;
	char			c;

	if (ft_strequ(conv->length_modifier, "l"))
		res = ft_get_wchar(va_arg(ap, wint_t));
	else
	{
		c = va_arg(ap, int);
		res = (unsigned char*)ft_strnew(1);
		res[0] = c;
	}
	return ((char*)res);
}

char	*s_conversion(t_conversion *conv, va_list ap)
{
	char	*res;
	char	*str;
	wchar_t	*wchar_str;

	if (ft_strequ(conv->length_modifier, "l"))
	{
		wchar_str = va_arg(ap, wchar_t *);
		if (wchar_str == NULL)
			res = ft_strdup("(null)");
		else
			res = ft_get_wchar_str(wchar_str, &conv->precision);
	}
	else
	{
		str = va_arg(ap, char *);
		if (str == NULL)
			res = ft_strdup("(null)");
		else
			res = ft_strdup(str);
	}
	return (res);
}

char	*p_percent_coversion(t_conversion *conv, va_list ap)
{
	char *res;

	if (conv->conversion_name == '%')
		res = ft_strdup("%");
	else
		res = ft_get_address(va_arg(ap, void *));
	return (res);
}
