/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unfinished_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 13:36:27 by njennes           #+#    #+#             */
/*   Updated: 2022/03/27 13:36:28 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	contains_unfinished_quotes(char *str)
{
	char	quote;
	size_t	i;

	quote = 0;
	i = 0;
	while (str[i])
	{
		if (!quote && (str[i] == '\'' || str[i] == '"'))
			quote = str[i];
		else if (quote == str[i])
			quote = 0;
		i++;
	}
	return (quote);
}
