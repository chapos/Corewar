/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_extended.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <eyevresh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 15:21:00 by eyevresh          #+#    #+#             */
/*   Updated: 2018/03/04 15:21:00 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static int	check_text_formation(char **input, char **color)
{
	if (ft_strncmp(*input, "{bol}", 5) == 0)
		*color = T_BOLD;
	else if (ft_strncmp(*input, "{und}", 5) == 0)
		*color = T_UNDERLINE;
	else if (ft_strncmp(*input, "{def}", 5) == 0)
		*color = T_DEFAULT;
	else if (ft_strncmp(*input, "{swp}", 5) == 0)
		*color = T_SWAP;
	else if (ft_strncmp(*input, "{n_s}", 5) == 0)
		*color = T_NO_SWAP;
	else if (ft_strncmp(*input, "{n_u}", 5) == 0)
		*color = T_NO_UNDERLINE;
	else
		return (0);
	return (1);
}

int			get_color(char **input, char **color)
{
	int check;

	check = 1;
	if (check_text_formation(input, color))
		;
	else if (ft_strncmp(*input, "{red}", 5) == 0)
		*color = FG_RED;
	else if (ft_strncmp(*input, "{cya}", 5) == 0)
		*color = FG_CYAN;
	else if (ft_strncmp(*input, "{yel}", 5) == 0)
		*color = FG_YELLOW;
	else if (ft_strncmp(*input, "{gre}", 5) == 0)
		*color = FG_GREEN;
	else if (ft_strncmp(*input, "{blu}", 5) == 0)
		*color = FG_BLUE;
	else if (ft_strncmp(*input, "{bla}", 5) == 0)
		*color = FG_BLACK;
	else if (ft_strncmp(*input, "{mag}", 5) == 0)
		*color = FG_MAGENTA;
	else if (ft_strncmp(*input, "{n_c}", 5) == 0)
		*color = FG_DEFAULT;
	else
		check = 0;
	*input += check ? 5 : 0;
	return (check);
}

void		handle_pos_width_prec(t_conversion *conv, va_list ap, int flag)
{
	va_list copy;
	int		i;

	va_copy(copy, ap);
	i = 1;
	if (flag == 1)
	{
		while (i++ < conv->width_arg_number)
			va_arg(copy, void *);
		conv->field_width = va_arg(copy, int);
	}
	else
	{
		while (i++ < conv->precision_arg_number)
			va_arg(copy, void *);
		conv->precision = va_arg(copy, int);
	}
	va_end(copy);
}

void		get_positional_conv(t_conversion *conv, va_list copy)
{
	int i;

	i = 1;
	while (i++ < conv->conv_arg_number)
		va_arg(copy, void *);
}
