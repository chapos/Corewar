/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_input_optimization.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <eyevresh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 16:12:00 by eyevresh          #+#    #+#             */
/*   Updated: 2018/02/23 13:20:44 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

void	optimize_length_modifier(t_conversion *new_conv)
{
	if (!ft_strchr("diouxXnaAeEfFgGcs", new_conv->conversion_name))
		ft_bzero(new_conv->length_modifier, 3);
	if (ft_strchr("aAeEfFgG", new_conv->conversion_name))
	{
		if (new_conv->length_modifier[0] != 'L')
			ft_bzero(new_conv->length_modifier, 3);
	}
	if (new_conv->conversion_name == 'c' || new_conv->conversion_name == 's')
	{
		if (new_conv->length_modifier[0] != 'l')
			ft_bzero(new_conv->length_modifier, 0);
	}
}

void	optimize_conv_id(t_conversion *new_conv)
{
	if (ft_strchr("DOUCS", new_conv->conversion_name)
			&& new_conv->conversion_name != '\0')
	{
		new_conv->conversion_name += 32;
		ft_strncat(new_conv->length_modifier, "l", 1);
	}
}

void	optimize_flags_modifier_id(t_conversion *new_conv)
{
	optimize_sharp_flag(new_conv);
	optimize_zero_minus_flag(new_conv);
	optimize_space_plus_flag(new_conv);
	optimize_apostrophe(new_conv);
	optimize_length_modifier(new_conv);
	optimize_conv_id(new_conv);
}

void	optimize_width_precision(t_conversion *new_conv)
{
	char *zero_ptr;

	if (new_conv->field_width < 0)
	{
		new_conv->field_width = FT_ABS(new_conv->field_width);
		if (!ft_strchr(new_conv->flags, '-'))
			ft_strncat(new_conv->flags, "-", 1);
		optimize_zero_minus_flag(new_conv);
	}
	if (ft_strchr("cn%krq", new_conv->conversion_name))
		new_conv->precision = -1;
	zero_ptr = ft_strchr(new_conv->flags, '0');
	if (new_conv->precision >= 0 &&
		ft_strchr("diouxX", new_conv->conversion_name))
	{
		if (zero_ptr)
			*zero_ptr = '.';
	}
	if (new_conv->conversion_name == 'p' && new_conv->precision != 0
			&& new_conv->precision != -1)
		new_conv->precision += 2;
}

char	*optimize_zero_or_negative_result(t_conversion *conv, char *result)
{
	if (ft_strequ(result, "0") &&
			!ft_strchr("aAfFgGeE", conv->conversion_name))
	{
		conv->zero_res = 1;
		if (conv->precision == 0)
			result[0] = '\0';
	}
	else if (result[0] == '-')
	{
		optimize_negative_value(conv);
		conv->n_r = 1;
		result = ft_strrev(result);
		result[ft_strlen(result) - 1] = '\0';
		result = ft_strrev(result);
	}
	return (result);
}
