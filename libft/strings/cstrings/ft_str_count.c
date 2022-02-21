/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_count.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 17:49:56 by                   #+#    #+#             */
/*   Updated: 2022/01/25 17:54:18 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_str_count(char *str, char c, int mode)
{
	size_t	i;
	size_t	count;

	if (!(mode == FT_EACH || mode == FT_UNIQUE || mode == FT_GROUPS))
		return (0);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			count++;
			if (mode != FT_EACH && str[i + 1] == c)
			{
				if (mode == FT_UNIQUE)
					count--;
				while (str[i + 1] == c)
					i++;
			}
		}
		i++;
	}
	return (count);
}
