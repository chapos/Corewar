/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_wchar_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <eyevresh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 22:34:00 by eyevresh          #+#    #+#             */
/*   Updated: 2018/02/23 17:16:21 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	get_byte_size(unsigned int curr_wchar)
{
	int byte_size;
	int bit_size;

	bit_size = ft_bit_len(curr_wchar);
	if (bit_size <= 7)
		byte_size = 1;
	else if (bit_size <= 11)
		byte_size = 2;
	else if (bit_size <= 16)
		byte_size = 3;
	else
		byte_size = 4;
	return (byte_size);
}

static char	*get_str_with_precision(wchar_t *str, int *precision)
{
	char			*res;
	char			*tmp;
	unsigned char	*curr_wchar;
	size_t			i;

	i = 0;
	res = ft_strnew(0);
	while (str[i])
	{
		if (*precision - get_byte_size(str[i]) >= 0)
		{
			tmp = res;
			curr_wchar = ft_get_wchar(str[i]);
			res = ft_strjoin(res, (char*)curr_wchar);
			ft_strdel(&tmp);
			free(curr_wchar);
			*precision -= get_byte_size(str[i]);
			i++;
		}
		else
			break ;
	}
	return (res);
}

char		*ft_get_wchar_str(wchar_t *str, int *precision)
{
	char			*res;
	char			*tmp;
	unsigned char	*curr_wchar;
	size_t			i;

	i = 0;
	if (*precision == -1)
	{
		res = ft_strnew(0);
		while (str[i])
		{
			tmp = res;
			curr_wchar = ft_get_wchar(str[i]);
			res = ft_strjoin(res, (char*)curr_wchar);
			ft_strdel(&tmp);
			free(curr_wchar);
			i++;
		}
	}
	else
		res = get_str_with_precision(str, precision);
	return (res);
}
