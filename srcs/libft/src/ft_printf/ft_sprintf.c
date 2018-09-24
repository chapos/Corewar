/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <eyevresh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 18:16:00 by eyevresh          #+#    #+#             */
/*   Updated: 2018/03/05 18:16:00 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int		ft_sprintf(char *str, const char *format, ...)
{
	va_list	ap;
	int		len;

	va_start(ap, format);
	len = ft_vsprintf(str, format, ap);
	va_end(ap);
	return (len);
}

int		ft_snprintf(char *str, size_t size, const char *format, ...)
{
	va_list ap;
	int		len;

	va_start(ap, format);
	len = ft_vsnprintf(str, size, format, ap);
	va_end(ap);
	return (len);
}

int		ft_vsprintf(char *str, const char *format, va_list ap)
{
	char *input;
	char *result;
	char *tmp_ptr;

	result = ft_strnew(0);
	input = (char*)format;
	while (*input != '\0')
	{
		tmp_ptr = result;
		if (*input == '%')
		{
			if (!do_conversion(ap, &result, &input, NULL))
			{
				ft_strdel(&result);
				return (-1);
			}
		}
		else
			get_text(&result, &input);
		ft_strdel(&tmp_ptr);
	}
	str = ft_strcpy(str, result);
	ft_strdel(&result);
	g_positional_arg = 0;
	return ((int)ft_strlen(str));
}

int		ft_vsnprintf(char *str, size_t size, const char *format, va_list ap)
{
	char *input;
	char *result;
	char *tmp_ptr;

	result = ft_strnew(0);
	input = (char*)format;
	while (*input != '\0')
	{
		tmp_ptr = result;
		if (*input == '%')
		{
			if (!do_conversion(ap, &result, &input, NULL))
			{
				ft_strdel(&result);
				return (-1);
			}
		}
		else
			get_text(&result, &input);
		ft_strdel(&tmp_ptr);
	}
	str = ft_strncpy(str, result, size - 1);
	ft_strdel(&result);
	g_positional_arg = 0;
	return ((int)ft_strlen(str));
}
