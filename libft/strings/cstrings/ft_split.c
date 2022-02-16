/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 13:52:10 by njennes           #+#    #+#             */
/*   Updated: 2021/11/09 16:16:13 by njennes          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static int	ft_count_words(char const *s, char c)
{
	int	words;

	words = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			words++;
			while (*s && *s != c)
				s++;
		}
	}
	return (words);
}

static void	ft_chop(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			*str = 0;
		str++;
	}
}

static void	ft_free_all(char *s, char **tab, int i)
{
	while (i--)
	{
		free(tab[i]);
	}
	free(tab[i]);
	free(tab);
	free(s);
}

static int	ft_get_words(char *str, int count, char **tab)
{
	int	i;

	i = 0;
	while (i < count)
	{
		while (!*str)
			str++;
		tab[i] = ft_strdup(str);
		if (!tab[i])
		{
			ft_free_all(str, tab, i);
			return (0);
		}
		str += ft_strlen(str);
		i++;
	}
	tab[i] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	*sdup;
	char	**tab;

	if (!s)
		return (NULL);
	tab = malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	sdup = ft_strdup(s);
	if (!sdup)
	{
		free(tab);
		return (NULL);
	}
	ft_chop(sdup, c);
	if (!ft_get_words(sdup, ft_count_words(s, c), tab))
		return (NULL);
	free(sdup);
	return (tab);
}
