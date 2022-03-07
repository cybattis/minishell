/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <cybattis@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:46:20 by njennes           #+#    #+#             */
/*   Updated: 2022/03/05 14:19:24 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include "minishell.h"

int	is_operator(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == '&')
		return (1);
	return (0);
}

int	is_redir_token(int token)
{
	if (token == TOKEN_REDIR_OUT || token == TOKEN_REDIR_OUT_APPEND ||
		token == TOKEN_REDIR_IN || token == TOKEN_REDIR_RDOC)
		return (1);
	return (0);
}

int	get_token_type(char *token, t_lexer *lexer, int handle_op)
{
	int	last_token;

	if (handle_op && ft_strlen(token) <= 2)
	{
		if (ft_strcmp(token, "|") == 0)
			return (TOKEN_PIPE);
		if (ft_strcmp(token, ">") == 0)
			return (TOKEN_REDIR_OUT);
		if (ft_strcmp(token, "<") == 0)
			return (TOKEN_REDIR_IN);
		if (ft_strcmp(token, ">>") == 0)
			return (TOKEN_REDIR_OUT_APPEND);
		if (ft_strcmp(token, "<<") == 0)
			return (TOKEN_REDIR_RDOC);
	}
	last_token = get_last_token_type(lexer);
	if (last_token == TOKEN_EMPTY || last_token == TOKEN_PIPE
		|| last_token == TOKEN_FILE)
		return (TOKEN_COMMAND);
	if (last_token == TOKEN_COMMAND || last_token == TOKEN_ARG)
		return (TOKEN_ARG);
	if (last_token == TOKEN_REDIR_OUT || last_token == TOKEN_REDIR_OUT_APPEND
		|| last_token == TOKEN_REDIR_IN || last_token == TOKEN_REDIR_RDOC)
		return (TOKEN_FILE);
	return (TOKEN_UNKNOWN);
}
