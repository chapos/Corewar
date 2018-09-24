/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 14:45:00 by eyevresh          #+#    #+#             */
/*   Updated: 2017/11/28 17:36:50 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int		*ft_range(int min, int max)
{
	int	*arr;
	int i;

	if (min >= max)
		return (0);
	i = 0;
	arr = (int*)malloc(sizeof(*arr) * (max - min));
	if (arr == NULL)
		return (NULL);
	while (min + i < max)
	{
		arr[i] = min + i;
		i++;
	}
	return (arr);
}
