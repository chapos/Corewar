/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_final.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <eyevresh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 19:27:00 by eyevresh          #+#    #+#             */
/*   Updated: 2018/02/23 14:10:31 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

char	*get_final_conversion_res(t_conversion *new_conv, char *result, int *h)
{
	if (new_conv->conversion_name == 'c' && ft_strlen(result) == 0 && h)
	{
		result = handle_c_conv_zero_result(new_conv, result, h);
		return (result);
	}
	if (ft_strchr("diouxXbaAeEfFgG", new_conv->conversion_name))
		result = optimize_zero_or_negative_result(new_conv, result);
	if (new_conv->conversion_name == 'o' && ft_strchr(new_conv->flags, '#'))
	{
		if (new_conv->zero_res == 1 && new_conv->precision <= 1)
			new_conv->precision = 1;
		else if (new_conv->precision <= (int)ft_strlen(result))
			new_conv->precision = (int)ft_strlen(result) + 1;
	}
	if (new_conv->precision >= 0 &&
			!ft_strchr("aAfFgGeE", new_conv->conversion_name))
		result = include_precision(new_conv, result);
	result = handle_flags(new_conv, result);
	if (new_conv->field_width > 0 && !ft_strchr(new_conv->flags, '0'))
	{
		if ((int)ft_strlen(result) < new_conv->field_width)
			result = include_field_width(new_conv, result);
	}
	return (result);
}

char	*include_precision(t_conversion *new_conv, char *result)
{
	if (ft_strchr("diouxXb", new_conv->conversion_name))
		result = handle_dioux_prec(new_conv, result);
	else if (new_conv->conversion_name == 's'
			|| new_conv->conversion_name == 'y')
		result = handle_s_prec(new_conv, result);
	else if (new_conv->conversion_name == 'p')
		result = handle_p_prec(new_conv, result);
	return (result);
}

char	*include_field_width(t_conversion *new_conv, char *result)
{
	char *tmp;

	tmp = ft_strnew(new_conv->field_width - ft_strlen(result));
	tmp = ft_memset(tmp, ' ', new_conv->field_width - ft_strlen(result));
	if (ft_strchr(new_conv->flags, '-'))
	{
		result = ft_realloc(result, (size_t)new_conv->field_width + 1);
		result = ft_strcat(result, tmp);
	}
	else
		result = ft_strjoin_front(result, tmp);
	ft_strdel(&tmp);
	return (result);
}

char	*handle_flags(t_conversion *conv, char *result)
{
	if (ft_strchr(conv->flags, '0'))
		result = handle_zero_flag(conv, result);
	if (conv->n_r == 1)
		result = handle_negative_result(conv, result);
	if (ft_strchr(conv->flags, '#'))
		result = handle_sharp_flag(conv, result);
	if (ft_strchr(conv->flags, '+'))
		result = handle_plus_flag(conv, result);
	if (ft_strchr(conv->flags, ' '))
		result = handle_space_flag(conv, result);
	return (result);
}

char	*handle_c_conv_zero_result(t_conversion *conv, char *result, int *h)
{
	*h = 1;
	if (conv->field_width > 1)
	{
		result = ft_realloc(result, conv->field_width);
		if (ft_strchr(conv->flags, '0'))
			result = ft_memset(result, '0', conv->field_width - 1);
		else
			result = ft_memset(result, ' ', conv->field_width - 1);
		if (ft_strchr(conv->flags, '-'))
			*h = 2;
	}
	return (result);
}
