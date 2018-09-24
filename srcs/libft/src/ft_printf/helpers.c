/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <eyevresh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 15:45:00 by eyevresh          #+#    #+#             */
/*   Updated: 2018/02/23 13:12:01 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

t_conv_map	g_conv_map[] =
{
	{'d', &di_conversion},
	{'i', &di_conversion},
	{'o', &ouxb_conversion},
	{'u', &ouxb_conversion},
	{'x', &ouxb_conversion},
	{'X', &ouxb_conversion},
	{'c', &c_conversion},
	{'s', &s_conversion},
	{'p', &p_percent_coversion},
	{'%', &p_percent_coversion},
	{'b', &ouxb_conversion},
	{'f', &f_conversion},
	{'F', &f_conversion},
	{'e', &e_conversion},
	{'E', &e_conversion},
	{'g', &g_conversion},
	{'G', &g_conversion},
	{'a', &a_conversion},
	{'A', &a_conversion},
	{'r', &r_conversion},
	{'k', &k_conversion},
	{'y', &y_conversion},
	{'q', &q_conversion},
};
int		g_positional_arg = 0;

void	handle_text(char **input, int *size, int fd)
{
	char	*str;
	size_t	len;

	str = *input;
	len = 0;
	len += str[len] == '{' ? 1 : 0;
	while (str[len] && str[len] != '%' && str[len] != '{')
		len++;
	write(fd, str, len);
	*size += len;
	*input += len;
}

int		handle_conversion(va_list ap, char **input, int *size, int fd)
{
	char	*result;
	char	*tmp_ptr;
	int		pure_hate;
	int		i;

	result = ft_strnew(0);
	tmp_ptr = result;
	pure_hate = 0;
	if ((i = do_conversion(ap, &result, input, &pure_hate)))
	{
		if (i != -1)
		{
			handle_n_conversion(*size, i, ap);
			print_conversion_result(result, pure_hate, size, fd);
			ft_strdel(&result);
			ft_strdel(&tmp_ptr);
		}
		return (i);
	}
	ft_strdel(&result);
	return (0);
}

void	print_conversion_result(char *result, int pure_hate, int *size, int fd)
{
	if (pure_hate > 0)
	{
		*size += 1;
		if (pure_hate == 1)
			write(fd, result, ft_strlen(result) + 1);
		else
		{
			write(fd, "\0", 1);
			write(fd, result, ft_strlen(result));
		}
	}
	else
		ft_putstr_fd(result, fd);
	*size += (int)ft_strlen(result);
}

void	get_text(char **result, char **input)
{
	char	*str;
	char	*buff;
	size_t	size;

	str = *input;
	size = 0;
	while (str[size] && str[size] != '%')
		size++;
	buff = ft_strnew(size);
	buff = ft_strncpy(buff, str, size);
	*result = ft_strjoin(*result, buff);
	*input += size;
	ft_strdel(&buff);
}

char	*get_base_for_conv(char c)
{
	char *base;

	if (c == 'o')
		base = "01234567";
	else if (c == 'x')
		base = "0123456789abcdef";
	else if (c == 'X')
		base = "0123456789ABCDEF";
	else if (c == 'b')
		base = "01";
	else
		base = "0123456789";
	return (base);
}
