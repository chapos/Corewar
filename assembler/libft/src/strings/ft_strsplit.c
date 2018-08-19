/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 15:53:45 by eyevresh          #+#    #+#             */
/*   Updated: 2017/12/22 19:56:42 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static char	**ft_splitalloctab(char **table, const char *str, char c)
{
	size_t i;
	size_t words;

	i = 0;
	words = 0;
	while (str[i] == c)
		i++;
	while (str[i] != '\0')
	{
		i++;
		if (str[i] == c)
		{
			words++;
			while (str[i] == c)
				i++;
		}
	}
	if (str[i - 1] != c)
		words++;
	table = (char**)malloc(sizeof(*table) * (words + 1));
	if (table == NULL)
		return (NULL);
	table[words] = 0;
	return (table);
}

static char	**ft_splitallocwords(char **table, const char *str, char c)
{
	size_t i;
	size_t word;
	size_t letters;

	i = 0;
	word = 0;
	letters = 1;
	while (str[i] == c)
		i++;
	while (str[i] != '\0')
	{
		i++;
		if (str[i] == c || str[i] == '\0')
		{
			table[word] = (char*)malloc(sizeof(**table) * (letters + 1));
			if (table[word] == NULL)
				return (NULL);
			word++;
			letters = 0;
			while (str[i] == c)
				i++;
		}
		letters++;
	}
	return (table);
}

static char	**ft_splitfilltab(char **table, const char *str, char c)
{
	size_t i;
	size_t word;
	size_t letter;

	i = 0;
	word = 0;
	letter = 0;
	while (str[i] == c)
		i++;
	while (str[i] != '\0')
	{
		table[word][letter] = str[i];
		letter++;
		i++;
		if (str[i] == c || str[i] == '\0')
		{
			table[word][letter] = '\0';
			word++;
			letter = 0;
			while (str[i] == c)
				i++;
		}
	}
	return (table);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**table;

	if (s == NULL)
		return (NULL);
	table = NULL;
	if (*s == '\0' || c == '\0')
	{
		table = (char**)malloc(sizeof(*table) * 1);
		if (table == NULL)
			return (NULL);
		table[0] = NULL;
		return (table);
	}
	table = ft_splitalloctab(table, s, c);
	if (table == NULL)
		return (NULL);
	table = ft_splitallocwords(table, s, c);
	if (table == NULL)
	{
		ft_del_arr_of_pointers((void**)table);
		return (NULL);
	}
	table = ft_splitfilltab(table, s, c);
	return (table);
}
