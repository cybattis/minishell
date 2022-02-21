/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 17:49:56 by                   #+#    #+#             */
/*   Updated: 2022/01/25 17:54:18 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_trimr(char *str)
{
	int	i;

	if (!str)
		return (NULL);
	i = ft_strlen(str) - 1;
	while (i >= 0 && ft_isspace(str[i]))
	{
		str[i] = 0;
		i--;
	}
	return (str);
}

char	*ft_triml(char *str)
{
	size_t	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && ft_isspace(str[i]))
	{
		str[i] = 0;
		i++;
	}
	return (&str[i]);
}

char	*ft_trim(char *str)
{
	ft_trimr(str);
	return (ft_triml(str));
}
