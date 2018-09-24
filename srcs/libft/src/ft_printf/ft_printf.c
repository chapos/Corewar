/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 15:10:57 by eyevresh          #+#    #+#             */
/*   Updated: 2018/02/23 13:27:54 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int		ft_printf(const char *format, ...)
{
	va_list ap;
	int		len;

	va_start(ap, format);
	len = ft_vdprintf(1, format, ap);
	va_end(ap);
	return (len);
}

int		ft_dprintf(int fd, const char *format, ...)
{
	va_list	ap;
	int		len;

	va_start(ap, format);
	len = ft_vdprintf(fd, format, ap);
	va_end(ap);
	return (len);
}

int		ft_asprintf(char **ret, const char *format, ...)
{
	va_list ap;
	int		len;

	va_start(ap, format);
	len = ft_vasprintf(ret, format, ap);
	va_end(ap);
	return (len);
}

int		ft_vdprintf(int fd, const char *format, va_list ap)
{
	char	*input;
	char	*color;
	int		size;

	input = (char*)format;
	size = 0;
	color = NULL;
	while (*input != '\0')
	{
		if (*input == '{' && get_color(&input, &color))
			color != NULL ? write(fd, color, ft_strlen(color)) : 0;
		else if (*input == '%')
		{
			if (handle_conversion(ap, &input, &size, fd) == -1)
				return (-1);
		}
		else
			handle_text(&input, &size, fd);
	}
	g_positional_arg = 0;
	return (size);
}

int		ft_vasprintf(char **ret, const char *format, va_list ap)
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
	*ret = result;
	g_positional_arg = 0;
	return ((int)ft_strlen(result));
}
