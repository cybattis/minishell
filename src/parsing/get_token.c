/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:46:20 by njennes           #+#    #+#             */
/*   Updated: 2022/03/05 14:19:24 by cybattis         ###   ########.fr       */
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
	if (last_token == TOKEN_EMPTY || last_token == TOKEN_PIPE)
		return (TOKEN_COMMAND);
	if (last_token == TOKEN_COMMAND || last_token == TOKEN_ARG)
		return (TOKEN_ARG);
	if (last_token == TOKEN_REDIR_OUT || last_token == TOKEN_REDIR_OUT_APPEND
		|| last_token == TOKEN_REDIR_IN || last_token == TOKEN_REDIR_RDOC)
		return (TOKEN_FILE);
	return (TOKEN_UNKNOWN);
}

t_token	consume_single_quotes(t_parser *parser, t_lexer *lexer)
{
	size_t	start;
	t_token	token;

	parser->i++;
	start = parser->i;
	while (parser->str[parser->i] &&
			parser->str[parser->i] != '\'')
		parser->i++;
	token.is_one_word = FT_TRUE;
	token.str = gc_substr(get_gc(), parser->str, start, parser->i - start);
	token.type = get_token_type(token.str, lexer, 0);
	parser->i++;
	return (token);
}

t_token	consume_double_quotes(t_parser *parser, t_lexer *lexer)
{
	size_t	start;
	t_token	token;

	parser->i++;
	start = parser->i;
	while (parser->str[parser->i] &&
			parser->str[parser->i] != '"')
		parser->i++;
	token.is_one_word = FT_TRUE;
	token.str = gc_substr(get_gc(), parser->str, start, parser->i - start);
	token.type = get_token_type(token.str, lexer, 0);
	parser->i++;
	return (token);
}

void	token_append(t_token new, t_token *token)
{
	token->str = gc_strjoin(get_gc(), token->str, new.str, 1);
	gc_free(get_gc(), new.str);
}

t_token	consume_word(t_parser *parser, t_lexer *lexer)
{
	int		is_op;
	t_token	token;

	is_op = is_operator(parser->str[parser->i]);
	token.str = gc_strdup(get_gc(), "");
	while (parser->str[parser->i] &&
			!ft_isspace(parser->str[parser->i]) &&
			is_op == is_operator(parser->str[parser->i]))
	{
		if (parser->str[parser->i] == '\'')
			token_append(consume_single_quotes(parser, lexer), &token);
		else if (parser->str[parser->i] == '"')
			token_append(consume_double_quotes(parser, lexer), &token);
		else
		{
			token.str = gc_strappend(get_gc(), token.str, parser->str[parser->i]);
			parser->i++;
		}
	}
	token.is_one_word = FT_TRUE;
	token.type = get_token_type(token.str, lexer, 1);
	return (token);
}
