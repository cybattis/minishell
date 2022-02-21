/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 13:52:10 by njennes           #+#    #+#             */
/*   Updated: 2021/11/09 16:16:13 by njennes          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

static int	ft_get_words(t_gc *gc, char *str, int count, char **tab)
{
	int	i;

	i = 0;
	while (i < count)
	{
		while (!*str)
			str++;
		tab[i] = gc_strdup(gc, str);
		str += ft_strlen(str);
		i++;
	}
	tab[i] = NULL;
	return (1);
}

char	**gc_split(t_gc *gc, char const *s, char c)
{
	char	*sdup;
	char	**tab;

	if (!s)
		return (NULL);
	tab = gc_calloc(gc, ft_count_words(s, c) + 1, sizeof(char *));
	sdup = gc_strdup(gc, s);
	ft_chop(sdup, c);
	if (!ft_get_words(gc, sdup, ft_count_words(s, c), tab))
		return (NULL);
	gc_free(gc, sdup);
	return (tab);
}
