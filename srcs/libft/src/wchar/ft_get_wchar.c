/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_wchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <eyevresh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 18:27:00 by eyevresh          #+#    #+#             */
/*   Updated: 2018/02/01 18:27:00 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static void		get_two_byte_wchar(unsigned char *res, unsigned int c)
{
	unsigned int	mask;
	unsigned char	o1;
	unsigned char	o2;

	mask = 49280;
	o2 = (c << 26) >> 26;
	o1 = ((c >> 6) << 27) >> 27;
	res[0] = (mask >> 8) | o1;
	res[1] = ((mask << 24) >> 24) | o2;
}

static void		get_three_byte_wchar(unsigned char *res, unsigned int c)
{
	unsigned int	mask;
	unsigned char	o1;
	unsigned char	o2;
	unsigned char	o3;

	mask = 14712960;
	o3 = (c << 26) >> 26;
	o2 = ((c >> 6) << 26) >> 26;
	o1 = ((c >> 12) << 28) >> 28;
	res[0] = (mask >> 16) | o1;
	res[1] = ((mask) << 16) >> 24 | o2;
	res[2] = ((mask << 24) >> 24) | o3;
}

static void		get_four_byte_wchar(unsigned char *res, unsigned int c)
{
	unsigned int	mask;
	unsigned char	o1;
	unsigned char	o2;
	unsigned char	o3;
	unsigned char	o4;

	mask = 4034953344;
	o4 = (c << 26) >> 26;
	o3 = ((c >> 6) << 26) >> 26;
	o2 = ((c >> 12) << 26) >> 26;
	o1 = ((c >> 18) << 29) >> 29;
	res[0] = (mask >> 24) | o1;
	res[1] = ((mask << 8) >> 24) | o2;
	res[2] = ((mask << 16) >> 24) | o3;
	res[3] = ((mask << 24) >> 24) | o4;
}

unsigned char	*ft_get_wchar(wint_t c)
{
	unsigned char	*res;
	size_t			bit_size;
	int				byte_size;

	res = (unsigned char*)ft_strnew(4);
	bit_size = ft_bit_len(c);
	if (bit_size <= 7)
		byte_size = 1;
	else if (bit_size <= 11)
		byte_size = 2;
	else if (bit_size <= 16)
		byte_size = 3;
	else
		byte_size = 4;
	if (byte_size > MB_CUR_MAX)
		res[0] = (char)c;
	else if (bit_size <= 7)
		res[0] = (unsigned char)c;
	else if (bit_size <= 11)
		get_two_byte_wchar(res, c);
	else if (bit_size <= 16)
		get_three_byte_wchar(res, c);
	else
		get_four_byte_wchar(res, c);
	return (res);
}
