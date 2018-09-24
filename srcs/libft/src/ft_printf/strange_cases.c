/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strange_cases.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 15:57:42 by eyevresh          #+#    #+#             */
/*   Updated: 2018/02/23 15:57:43 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

char	*reset_for_p_conv(char *result)
{
	size_t i;

	i = 2;
	while (result[i])
	{
		result[i - 2] = result[i];
		i++;
	}
	result[i - 2] = '\0';
	return (result);
}

char	*handle_p_width(char *result, char *tmp)
{
	result = reset_for_p_conv(result);
	result = ft_strjoin_front(result, tmp);
	result = ft_strjoin_front(result, "0x");
	return (result);
}

int		get_n_conversion(t_conversion *conv, char **result)
{
	int flag;

	flag = 2;
	if (ft_strequ(conv->length_modifier, "h"))
		flag = 3;
	else if (ft_strequ(conv->length_modifier, "hh"))
		flag = 4;
	else if (ft_strequ(conv->length_modifier, "l"))
		flag = 5;
	else if (ft_strequ(conv->length_modifier, "ll"))
		flag = 6;
	else if (ft_strequ(conv->length_modifier, "j"))
		flag = 7;
	else if (ft_strequ(conv->length_modifier, "z"))
		flag = 8;
	*result = ft_strjoin(*result, "");
	free(conv);
	return (flag);
}

void	handle_n_conversion(int size, int flag, va_list ap)
{
	void *ptr;

	if (flag > 1)
	{
		if (flag == 3)
			ptr = va_arg(ap, short *);
		else if (flag == 4)
			ptr = va_arg(ap, char *);
		else if (flag == 5)
			ptr = va_arg(ap, long *);
		else if (flag == 6)
			ptr = va_arg(ap, long long *);
		else if (flag == 7)
			ptr = va_arg(ap, intmax_t *);
		else if (flag == 8)
			ptr = va_arg(ap, ssize_t *);
		else
			ptr = va_arg(ap, int *);
		*(int*)ptr = size;
	}
}

char	*y_conversion(t_conversion *conv, va_list ap)
{
	char	*result;
	ssize_t	size;
	int		fd;

	(void)conv;
	result = ft_strnew(42);
	fd = va_arg(ap, int);
	if (fd != -1)
	{
		while ((size = read(fd, result, 42)))
			result = ft_realloc(result, ft_strlen(result) + 43);
	}
	return (result);
}
