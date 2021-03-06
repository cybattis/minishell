/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 13:36:21 by njennes           #+#    #+#             */
/*   Updated: 2022/03/27 13:36:22 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

int	is_operator_char(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

char	*skip_spaces(char *str)
{
	while (ft_isspace(*str))
		str++;
	return (str);
}

size_t	skip_quotes(char *str)
{
	size_t	i;
	char	quote;

	quote = *str;
	if (!(quote == '\'' || quote == '"'))
		return (0);
	i = 1;
	while (str[i] && str[i] != quote)
		i++;
	if (str[i] == quote)
		i++;
	return (i);
}

int	contains_open_spaces(char *str)
{
	char	quote;
	size_t	i;

	quote = 0;
	i = 0;
	while (str[i])
	{
		if (!quote && str[i] == '"')
			quote = '"';
		else if (quote == '"' && str[i] == '"')
			quote = 0;
		else if (!quote && str[i] == '\'')
			quote = '\'';
		else if (quote == '\'' && str[i] == '\'')
			quote = 0;
		if (!quote && ft_isspace(str[i]))
			return ((int)i);
		i++;
	}
	return (0);
}
