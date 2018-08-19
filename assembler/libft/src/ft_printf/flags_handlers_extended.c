/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_handlers_extended.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <eyevresh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 17:17:00 by eyevresh          #+#    #+#             */
/*   Updated: 2018/02/27 17:17:00 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static void	put_comma(char *result, int pos, struct lconv *local_struct)
{
	int len;

	pos += result[0] == '-' ? 1 : 0;
	len = ft_strlen(result);
	while (len > pos)
	{
		result[len] = result[len - 1];
		len--;
	}
	result[pos] = *local_struct->thousands_sep;
}

static void	get_result(char *result, int counter, int len, struct lconv *l_s)
{
	int i;

	i = len % 3;
	i += i == 0 ? 3 : 0;
	while (counter)
	{
		put_comma(result, i, l_s);
		counter--;
		i += 4;
	}
}

char		*handle_apostrophe_flag(char *result)
{
	struct lconv	*local_struct;
	size_t			i;
	int				counter;

	local_struct = localeconv();
	if (*local_struct->thousands_sep == ',')
	{
		i = 0;
		while (result[i] != '.' && result[i])
			i++;
		i -= result[0] == '-' ? 1 : 0;
		if (i > 3)
		{
			counter = (i - 1) / 3;
			result = ft_realloc(result, ft_strlen(result) + counter + 1);
			get_result(result, counter, i, local_struct);
		}
	}
	return (result);
}
