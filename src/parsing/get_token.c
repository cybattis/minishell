/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:46:20 by njennes           #+#    #+#             */
/*   Updated: 2022/02/16 22:17:25 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include "minishell.h"

int	get_token_type(char *token, t_lexer *lexer)
{
	int	last_token;

	if (ft_strlen(token) <= 2)
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
			return (TOKEN_REDIR_IN_APPEND);
	}
	last_token = get_last_token_type(lexer);
	if (last_token == TOKEN_EMPTY || last_token == TOKEN_PIPE ||
		last_token == TOKEN_REDIR_IN || last_token == TOKEN_REDIR_IN_APPEND)
		return (TOKEN_COMMAND);
	if (last_token == TOKEN_COMMAND || last_token == TOKEN_ARG)
		return (TOKEN_ARG);
	if (last_token == TOKEN_REDIR_OUT || last_token == TOKEN_REDIR_OUT_APPEND)
		return (TOKEN_ARG);
	return (TOKEN_UNKNOWN);
}

void	consume_single_quotes(t_parser *parser, t_lexer *lexer)
{
	size_t	size;
	t_token	token;

	size = 1;
	while (parser->str[parser->i + size] &&
			parser->str[parser->i + size] != '\'')
		size++;
	size++;
	token.is_one_word = FT_TRUE;
	token.str = gc_substr(get_gc(), parser->str, parser->i, size);
	token.type = get_token_type(token.str, lexer);
	lexer_add_token(token, lexer);
	parser->i += size;
}

void	consume_double_quotes(t_parser *parser, t_lexer *lexer)
{
	size_t	size;
	t_token	token;

	size = 1;
	while (parser->str[parser->i + size] &&
			parser->str[parser->i + size] != '"')
		size++;
	size++;
	token.is_one_word = FT_TRUE;
	token.str = gc_substr(get_gc(), parser->str, parser->i, size);
	token.type = get_token_type(token.str, lexer);
	lexer_add_token(token, lexer);
	parser->i += size;
}

void	consume_word(t_parser *parser, t_lexer *lexer)
{
	size_t	size;
	t_token	token;

	size = ft_word_size(&parser->str[parser->i]);
	token.is_one_word = FT_TRUE;
	token.str = gc_substr(get_gc(), parser->str, parser->i, size);
	token.type = get_token_type(token.str, lexer);
	lexer_add_token(token, lexer);
	parser->i += size;
}
