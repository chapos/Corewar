/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <eyevresh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 17:15:00 by eyevresh          #+#    #+#             */
/*   Updated: 2018/02/07 17:15:00 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

char	*handle_sharp_flag(t_conversion *conv, char *result)
{
	if (conv->conversion_name == 'x')
	{
		if (ft_strlen(result) > 0 && conv->zero_res != 1)
			result = ft_strjoin_front(result, "0x");
	}
	else if (conv->conversion_name == 'X')
	{
		if (ft_strlen(result) > 0 && conv->zero_res != 1)
			result = ft_strjoin_front(result, "0X");
	}
	return (result);
}

char	*handle_plus_flag(t_conversion *conv, char *result)
{
	char *tmp;

	if (ft_strchr("aAdeEfFgGi", conv->conversion_name))
	{
		tmp = ft_strdup("+");
		result = ft_strjoin_front(result, tmp);
		ft_strdel(&tmp);
	}
	return (result);
}

char	*handle_space_flag(t_conversion *conv, char *result)
{
	char *tmp;

	if (ft_strchr("aAdeEfFgGi", conv->conversion_name))
	{
		tmp = ft_strdup(" ");
		result = ft_strjoin_front(result, tmp);
		ft_strdel(&tmp);
	}
	return (result);
}

char	*handle_zero_flag(t_conversion *c, char *result)
{
	int		f;
	char	*tmp;

	f = 0;
	if (c->n_r == 1 || ft_strchr(c->flags, ' ') || ft_strchr(c->flags, '+'))
		f = 1;
	else if (ft_strchr(c->flags, '#') && c->zero_res != 1
			&& !ft_strchr("oaAfFgGeE", c->conversion_name))
		f = 2;
	if ((int)ft_strlen(result) < c->field_width - f)
	{
		tmp = ft_strnew(c->field_width - (int)ft_strlen(result) - f);
		tmp = ft_memset(tmp, '0', c->field_width - (int)ft_strlen(result) - f);
		if (c->conversion_name == 'p')
			result = handle_p_width(result, tmp);
		else
			result = ft_strjoin_front(result, tmp);
		ft_strdel(&tmp);
	}
	return (result);
}

char	*handle_negative_result(t_conversion *conv, char *result)
{
	char *tmp;

	if (ft_strchr("aAdeEfFgGi", conv->conversion_name))
	{
		tmp = ft_strdup("-");
		result = ft_strjoin_front(result, tmp);
		ft_strdel(&tmp);
	}
	return (result);
}
