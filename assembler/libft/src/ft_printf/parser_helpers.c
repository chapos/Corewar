/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <eyevresh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 17:42:00 by eyevresh          #+#    #+#             */
/*   Updated: 2018/03/09 14:42:03 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int		check_if_positional_width(t_conversion *conv, char *str, size_t *i)
{
	size_t j;

	j = 1;
	while (ft_isdigit(str[j]))
		j++;
	if (str[j] == '$')
	{
		if (j != 1)
			conv->width_arg_number = ft_atoi(str + 1);
		else
			conv->width_arg_number = -1;
		g_positional_arg = 1;
		*i += j == 1 ? 1 : j - 1 + 1;
		return (1);
	}
	return (0);
}

int		check_if_positional_prec(t_conversion *conv, char *str, size_t *i)
{
	size_t j;

	j = 2;
	while (ft_isdigit(str[j]))
		j++;
	if (str[j] == '$')
	{
		if (j != 2)
			conv->precision_arg_number = ft_atoi(str + 2);
		else
			conv->precision_arg_number = -1;
		g_positional_arg = 1;
		*i += j == 2 ? 1 : j - 2 + 1;
		return (1);
	}
	return (0);
}

void	get_conversion_id(t_conversion *new_conv, char **input)
{
	new_conv->conversion_name = **input;
	if (**input != '\0')
		(*input)++;
}

int		validate_conv_input(t_conversion *conv)
{
	if (g_positional_arg)
	{
		if (conv->conv_arg_number <= 0 || conv->width_arg_number == 0
				|| conv->precision_arg_number == 0)
		{
			free(conv);
			return (-1);
		}
	}
	return (1);
}
