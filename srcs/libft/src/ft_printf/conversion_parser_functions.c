/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_parser_functions.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <eyevresh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 19:44:00 by eyevresh          #+#    #+#             */
/*   Updated: 2018/02/23 13:09:13 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

void	get_pos_arg_number(t_conversion *new_conv, char **input)
{
	char	*str;
	size_t	i;

	str = *input;
	i = 0;
	if (ft_isdigit(str[i]))
	{
		while (ft_isdigit(str[i]))
			i++;
		if (str[i] == '$')
		{
			new_conv->conv_arg_number = ft_atoi(str);
			g_positional_arg = 1;
			*input += (i + 1);
		}
	}
}

void	get_flags(t_conversion *new_conv, char **input)
{
	char	*str;
	size_t	i;

	str = *input;
	i = 0;
	while (str[i])
	{
		if (ft_strchr("#0-+ '", str[i]))
		{
			if (!ft_strchr(new_conv->flags, str[i]))
				ft_strncat(new_conv->flags, str + i, 1);
		}
		else
			break ;
		i++;
	}
	*input += i;
}

void	get_field_width(t_conversion *new_conv, char **input, va_list ap)
{
	char	*str;
	size_t	i;
	size_t	j;

	str = *input;
	i = 0;
	while (str[i] == '*' || ft_isdigit(str[i]))
	{
		if (str[i] == '*')
		{
			i++;
			if (!check_if_positional_width(new_conv, str, &i))
				new_conv->field_width = va_arg(ap, int);
		}
		j = 0;
		while (ft_isdigit(str[i + j]))
			j++;
		if (j != 0)
			new_conv->field_width = ft_atoi(str + i);
		i += j;
	}
	*input += i;
}

void	get_precision(t_conversion *new_conv, char **input, va_list ap)
{
	char	*str;
	size_t	i;
	size_t	j;

	str = *input;
	i = 0;
	while (str[i] == '.')
	{
		i++;
		if (str[i] == '*')
		{
			i++;
			if (!check_if_positional_prec(new_conv, str, &i))
				new_conv->precision = va_arg(ap, int);
		}
		else
			new_conv->precision = ft_atoi(str + i);
		j = 0;
		while (ft_isdigit(str[i + j]))
			j++;
		i += j;
	}
	*input += i;
}

void	get_length_modifier(t_conversion *new_conv, char **input)
{
	char	*str;

	str = *input;
	if (str[0] == 'z')
		ft_strcpy(new_conv->length_modifier, "z");
	else if (str[0] == 'j')
		ft_strcpy(new_conv->length_modifier, "j");
	else if (str[0] == 'l' && str[1] == 'l')
		ft_strcpy(new_conv->length_modifier, "ll");
	else if (str[0] == 'L')
		ft_strcpy(new_conv->length_modifier, "L");
	else if (str[0] == 'l' && str[1] != 'l')
		ft_strcpy(new_conv->length_modifier, "l");
	else if (str[0] == 'h' && str[1] != 'h')
		ft_strcpy(new_conv->length_modifier, "h");
	else if (str[0] == 'h' && str[1] == 'h')
		ft_strcpy(new_conv->length_modifier, "hh");
	else
		ft_strcpy(new_conv->length_modifier, "");
	*input += ft_strlen(new_conv->length_modifier);
}
