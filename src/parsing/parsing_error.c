/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:46:20 by njennes           #+#    #+#             */
/*   Updated: 2022/02/16 22:17:25 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../libft/libft.h"

static int	check_token_order(int last, int current)
{
	if (last == TOKEN_PIPE && current == TOKEN_PIPE)
		return (0);
	return (1);
}

int	check_parsing_errors(t_lexer lexer)
{
	int		last_token;
	int		token;
	size_t	i;

	i = 0;
	last_token = TOKEN_EMPTY;
	while (i < lexer.count)
	{
		token = lexer.tokens[i].type;
		if (i == 0 && !(token == TOKEN_COMMAND || token == TOKEN_REDIR_IN || token == TOKEN_REDIR_RDOC))
			return (0);
		if (!check_token_order(last_token, token))
			return (0);
		last_token = token;
		i++;
	}
	return (1);
}
