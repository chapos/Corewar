/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:27:50 by eyevresh          #+#    #+#             */
/*   Updated: 2017/11/28 19:55:14 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#define SPACE(c) ((c) == ' ' || (c) == '\n' || (c) == '\t')

static size_t	ft_strsize_no_edgespace(char const *s)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (s[i] != '\0' && SPACE(s[i]))
		i++;
	while (s[j] != '\0')
		j++;
	j--;
	while (SPACE(s[j]) && j != 0)
		j--;
	return (j - i + 1);
}

char			*ft_strtrim(char const *s)
{
	char	*new_str;
	size_t	size;

	if (s == NULL)
		return (NULL);
	size = ft_strsize_no_edgespace(s);
	while (*s != '\0' && SPACE(*s))
		s++;
	if (*s != '\0')
	{
		new_str = (char*)malloc(sizeof(char) * (size + 1));
		if (new_str == NULL)
			return (NULL);
		new_str = ft_strncpy(new_str, s, size);
		new_str[size] = '\0';
	}
	else
	{
		new_str = (char*)malloc(sizeof(char) * 1);
		if (new_str == NULL)
			return (NULL);
		new_str[0] = '\0';
	}
	return (new_str);
}
