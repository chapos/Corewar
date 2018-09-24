/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <eyevresh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 17:14:00 by eyevresh          #+#    #+#             */
/*   Updated: 2018/02/23 11:51:05 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

t_conversion	*alloc_new_conversion(void)
{
	t_conversion *new_conv;

	if (!(new_conv = (t_conversion*)malloc(sizeof(t_conversion))))
		return (NULL);
	new_conv->conv_arg_number = 0;
	ft_bzero(new_conv->flags, 7);
	new_conv->field_width = 0;
	new_conv->width_arg_number = -1;
	new_conv->precision = -1;
	new_conv->precision_arg_number = -1;
	ft_bzero(new_conv->length_modifier, 3);
	new_conv->conversion_name = '\0';
	new_conv->zero_res = 0;
	new_conv->n_r = 0;
	return (new_conv);
}

t_conversion	*get_conv_data(char **input, va_list ap)
{
	t_conversion	*new_conv;

	if (!(new_conv = alloc_new_conversion()))
		return (NULL);
	(*input)++;
	get_pos_arg_number(new_conv, input);
	get_flags(new_conv, input);
	get_field_width(new_conv, input, ap);
	get_precision(new_conv, input, ap);
	get_length_modifier(new_conv, input);
	get_conversion_id(new_conv, input);
	if (validate_conv_input(new_conv) == -1)
		return (NULL);
	optimize_flags_modifier_id(new_conv);
	return (new_conv);
}

char			*positional_conversion(t_conversion *c, va_list ap, int *h)
{
	char	*conv_result;
	va_list	copy;
	size_t	i;

	if (c->width_arg_number > 0)
		handle_pos_width_prec(c, ap, 1);
	if (c->precision_arg_number > 0)
		handle_pos_width_prec(c, ap, 2);
	optimize_width_precision(c);
	va_copy(copy, ap);
	get_positional_conv(c, copy);
	i = 0;
	while (c->conversion_name != g_conv_map[i].id && i < 22)
		i++;
	c->conv_map = g_conv_map[i];
	if (ft_strchr("sSpdDioOuUxXcCeEfFgGaA%brkyq", c->conversion_name))
		conv_result = (c->conv_map.conv_func)(c, copy);
	else
		conv_result = ft_strdup(&c->conversion_name);
	if (ft_strchr(c->flags, '\''))
		conv_result = handle_apostrophe_flag(conv_result);
	conv_result = get_final_conversion_res(c, conv_result, h);
	va_end(copy);
	return (conv_result);
}

char			*unpositional_conversion(t_conversion *c, va_list ap, int *h)
{
	char		*conv_result;
	size_t		i;

	optimize_width_precision(c);
	i = 0;
	while (c->conversion_name != g_conv_map[i].id && i < 22)
		i++;
	c->conv_map = g_conv_map[i];
	if (ft_strchr("sSpdDioOuUxXcCeEfFgGaA%brkyq", c->conversion_name))
		conv_result = (c->conv_map.conv_func)(c, ap);
	else
		conv_result = ft_strdup(&c->conversion_name);
	if (ft_strchr(c->flags, '\''))
		conv_result = handle_apostrophe_flag(conv_result);
	conv_result = get_final_conversion_res(c, conv_result, h);
	return (conv_result);
}

int				do_conversion(va_list ap, char **result, char **input, int *h)
{
	t_conversion	*new_conv;
	char			*conv_result;

	if (!(new_conv = get_conv_data(input, ap)))
	{
		ft_putstr_fd("You mixed positional args with non-positional!\n", 1);
		g_positional_arg = 0;
		return (-1);
	}
	if (new_conv->conversion_name == 'n')
		return (get_n_conversion(new_conv, result));
	if (**input == '\0' && new_conv->conversion_name == '\0')
		conv_result = ft_strnew(0);
	else if (g_positional_arg)
		conv_result = positional_conversion(new_conv, ap, h);
	else
		conv_result = unpositional_conversion(new_conv, ap, h);
	*result = ft_strjoin(*result, conv_result);
	ft_strdel(&conv_result);
	free(new_conv);
	return (1);
}
