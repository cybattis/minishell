/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:26:44 by njennes           #+#    #+#             */
/*   Updated: 2021/11/05 14:37:24 by njennes          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2, int to_free)
{
	size_t	new_len;
	size_t	copied;
	char	*new;

	if (!s1 || !s2)
		return (NULL);
	new_len = (ft_strlen(s1) + ft_strlen(s2) + 1);
	new = ft_calloc(new_len, sizeof (char));
	if (!new)
		return (NULL);
	copied = ft_strlcpy(new, s1, new_len);
	ft_strlcpy(&new[copied], s2, new_len - copied);
	if (to_free == 1 || to_free == 3)
		free(s1);
	if (to_free == 2 || to_free == 3)
		free(s2);
	return (new);
}
