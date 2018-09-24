/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_conversion_functions.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <eyevresh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 17:27:00 by eyevresh          #+#    #+#             */
/*   Updated: 2018/02/28 17:27:00 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static char	*get_non_printable_char(char *result, char c)
{
	char *tmp;

	tmp = ft_strjoin_front(ft_ctoa_base(c, "0123456789abcdef"), "0x");
	if (ft_isprint(c))
		result = ft_strjoin(result, &c);
	else if (c == '\a')
		result = ft_strjoin(result, "\\a");
	else if (c == '\b')
		result = ft_strjoin(result, "\\b");
	else if (c == '\f')
		result = ft_strjoin(result, "\\f");
	else if (c == '\n')
		result = ft_strjoin(result, "\\n");
	else if (c == '\r')
		result = ft_strjoin(result, "\\r");
	else if (c == '\t')
		result = ft_strjoin(result, "\\t");
	else if (c == '\v')
		result = ft_strjoin(result, "\\v");
	else if (c == '\0')
		result = ft_strjoin(result, "\\0");
	else
		result = ft_strjoin(result, tmp);
	ft_strdel(&tmp);
	return (result);
}

char		*r_conversion(t_conversion *conv, va_list ap)
{
	char	*result;
	char	*tmp_ptr;
	char	*tmp;
	size_t	i;

	(void)conv;
	tmp = va_arg(ap, char *);
	result = ft_strnew(0);
	i = 0;
	while (tmp[i])
	{
		tmp_ptr = result;
		result = get_non_printable_char(result, tmp[i]);
		ft_strdel(&tmp_ptr);
		i++;
	}
	tmp_ptr = result;
	result = get_non_printable_char(result, tmp[i]);
	ft_strdel(&tmp_ptr);
	return (result);
}

static void	get_date(struct tm *time_s, char *result)
{
	char *tmp;

	tmp = ft_itoa_base(time_s->tm_year + 1900, "0123456789");
	result = ft_strcat(result, tmp);
	result = ft_strcat(result, "-");
	ft_strdel(&tmp);
	tmp = ft_itoa_base(time_s->tm_mon + 1, "0123456789");
	result = ft_strcat(result, tmp);
	result = ft_strcat(result, "-");
	ft_strdel(&tmp);
	tmp = ft_itoa_base(time_s->tm_mday, "0123456789");
	result = ft_strcat(result, tmp);
	result = ft_strcat(result, "T");
	ft_strdel(&tmp);
}

static void	get_time(struct tm *time_s, char *result)
{
	char *tmp;

	tmp = ft_itoa_base(time_s->tm_hour, "0123456789");
	result = ft_strcat(result, tmp);
	result = ft_strcat(result, ":");
	ft_strdel(&tmp);
	tmp = ft_itoa_base(time_s->tm_min, "0123456789");
	result = ft_strcat(result, tmp);
	result = ft_strcat(result, ":");
	ft_strdel(&tmp);
	tmp = ft_itoa_base(time_s->tm_sec, "0123456789");
	result = ft_strcat(result, tmp);
	ft_strdel(&tmp);
}

char		*k_conversion(t_conversion *conv, va_list ap)
{
	char		*result;
	time_t		t;
	struct tm	*time_s;

	t = time(NULL);
	time_s = localtime(&t);
	(void)ap;
	(void)conv;
	result = ft_strnew(19);
	get_date(time_s, result);
	get_time(time_s, result);
	return (result);
}
