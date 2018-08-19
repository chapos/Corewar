/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precision_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 13:56:31 by eyevresh          #+#    #+#             */
/*   Updated: 2018/02/23 13:56:34 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

char	*handle_dioux_prec(t_conversion *new_conv, char *result)
{
	char *tmp;

	if (new_conv->precision > (int)ft_strlen(result))
	{
		tmp = ft_strnew(new_conv->precision - ft_strlen(result));
		tmp = ft_memset(tmp, '0', new_conv->precision - ft_strlen(result));
		result = ft_strjoin_front(result, tmp);
		ft_strdel(&tmp);
	}
	return (result);
}

char	*handle_s_prec(t_conversion *new_conv, char *result)
{
	if (!ft_strchr(new_conv->length_modifier, 'l'))
	{
		if ((int)ft_strlen(result) > new_conv->precision)
			result[new_conv->precision] = '\0';
	}
	return (result);
}

char	*handle_p_prec(t_conversion *new_conv, char *result)
{
	char *tmp;

	if (new_conv->precision > (int)ft_strlen(result))
	{
		tmp = ft_strnew(new_conv->precision - ft_strlen(result));
		tmp = ft_memset(tmp, '0', new_conv->precision - ft_strlen(result));
		result = reset_for_p_conv(result);
		result = ft_strjoin_front(result, tmp);
		result = ft_strjoin_front(result, "0x");
		ft_strdel(&tmp);
	}
	else if (ft_strlen(result) == 3)
		result[new_conv->precision + 2] = '\0';
	return (result);
}
