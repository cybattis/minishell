/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_split_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 14:12:32 by njennes           #+#    #+#             */
/*   Updated: 2022/03/27 14:12:33 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"

int	skip_quotes_command_split(char *str, size_t *i, int *encountered_char)
{
	if (str[*i] == '"' || str[*i] == '\'')
	{
		*encountered_char = 1;
		*i += skip_quotes(&str[*i]);
		return (1);
	}
	return (0);
}

int	last_char_is_pipe(char *str, size_t *i)
{
	if (*i > 0 && str[*i - 1] == '|')
	{
		(*i)++;
		return (1);
	}
	return (0);
}

int	is_legal_pipe(int *encountered_char, int *count)
{
	if (*encountered_char)
	{
		(*count)++;
		*encountered_char = 0;
		return (1);
	}
	return (0);
}
