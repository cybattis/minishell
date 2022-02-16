/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 16:10:13 by                   #+#    #+#             */
/*   Updated: 2022/01/25 17:52:27 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static int	get_index(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ft_tolower(c) && str[i] != ft_toupper(c))
		i++;
	return (i);
}

long	ft_atol_base(char *str, char *base)
{
	int		i;
	int		base_len;
	long	result;
	int		negative;

	i = 0;
	result = 0;
	negative = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			negative = -1;
		i++;
	}
	base_len = ft_strlen(base);
	while (str[i] && ft_isalnum(str[i]))
	{
		result = result * base_len + get_index(str[i], base);
		i++;
	}
	return (result * negative);
}
