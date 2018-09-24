/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_optimization.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <eyevresh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 16:43:00 by eyevresh          #+#    #+#             */
/*   Updated: 2018/01/26 16:43:00 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

void	optimize_sharp_flag(t_conversion *conv)
{
	char *ptr;

	if ((ptr = ft_strchr(conv->flags, '#')))
	{
		if (ft_strchr("cdinpsurkybq", conv->conversion_name))
			*ptr = '.';
	}
}

void	optimize_zero_minus_flag(t_conversion *conv)
{
	char *zero_ptr;
	char *minus_ptr;

	if ((minus_ptr = ft_strchr(conv->flags, '-')))
	{
		if (conv->conversion_name == 'n')
			*minus_ptr = '.';
	}
	if ((zero_ptr = ft_strchr(conv->flags, '0')))
	{
		if (minus_ptr)
			*zero_ptr = '.';
		else if (ft_strchr("n", conv->conversion_name))
			*zero_ptr = '.';
	}
}

void	optimize_space_plus_flag(t_conversion *conv)
{
	char *plus_ptr;
	char *space_ptr;

	if ((plus_ptr = ft_strchr(conv->flags, '+')))
	{
		if (!ft_strchr("aAdeEfFgGi", conv->conversion_name))
			*plus_ptr = '.';
	}
	if ((space_ptr = ft_strchr(conv->flags, ' ')))
	{
		if (plus_ptr)
			*space_ptr = '.';
		else if (!ft_strchr("aAdeEfFgGi", conv->conversion_name))
			*space_ptr = '.';
	}
}

void	optimize_apostrophe(t_conversion *conv)
{
	char *ptr;

	if ((ptr = ft_strchr(conv->flags, '\'')))
	{
		if (!ft_strchr("duifF", conv->conversion_name))
			*ptr = '.';
	}
}

void	optimize_negative_value(t_conversion *conv)
{
	char *ptr;

	ptr = ft_strchr(conv->flags, '+');
	if (ptr != NULL)
		*ptr = '.';
	ptr = ft_strchr(conv->flags, ' ');
	if (ptr != NULL)
		*ptr = '.';
}
