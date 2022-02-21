/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:27:03 by njennes           #+#    #+#             */
/*   Updated: 2021/11/05 17:29:38 by njennes          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_min(int a, int b)
{
	if (a > b)
		return (b);
	return (a);
}

char	*gc_substr(t_gc *gc, char const *s, unsigned int start, size_t len)
{
	char	*new;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (gc_strdup(gc, ""));
	new = gc_calloc(gc, ft_min(ft_strlen(s) - start, len) + 1, sizeof(char));
	ft_strlcpy(new, &s[start], ft_min(ft_strlen(s) - start, len) + 1);
	return (new);
}
