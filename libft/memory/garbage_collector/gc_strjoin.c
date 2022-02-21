/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:26:44 by njennes           #+#    #+#             */
/*   Updated: 2021/11/05 14:37:24 by njennes          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*gc_strjoin(t_gc *gc, char *s1, char *s2, int to_free)
{
	size_t	new_len;
	size_t	copied;
	char	*new;

	if (!s1 || !s2)
		return (NULL);
	new_len = (ft_strlen(s1) + ft_strlen(s2) + 1);
	new = gc_calloc(gc, new_len, sizeof (char));
	copied = ft_strlcpy(new, s1, new_len);
	ft_strlcpy(&new[copied], s2, new_len - copied);
	if (to_free == 1 || to_free == 3)
		gc_free(gc, s1);
	if (to_free == 2 || to_free == 3)
		gc_free(gc, s2);
	return (new);
}
