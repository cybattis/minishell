/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:46:20 by njennes           #+#    #+#             */
/*   Updated: 2022/03/08 12:20:54 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include "minishell.h"

static void	token_append(t_token new, t_token *token);

t_token	consume_single_quotes(t_parser *parser, t_lexer *lexer)
{
	size_t	start;
	t_token	token;

	parser->i++;
	start = parser->i;
	while (parser->str[parser->i] && parser->str[parser->i] != '\'')
		parser->i++;
	token.str = gc_substr(get_gc(), parser->str, start, parser->i - start);
	token.type = get_token_type(token.str, lexer, 0);
	parser->i++;
	return (token);
}

t_token	consume_double_quotes(t_parser *parser, t_lexer *lexer)
{
	t_token	token;

	parser->i++;
	token.str = gc_strdup(get_gc(), "");
	while (parser->str[parser->i] && parser->str[parser->i] != '"')
	{
		if (parser->str[parser->i] == '$')
			handle_dollar_sign(parser, lexer, 0, &token);
		else
		{
			token.str = gc_strappend(get_gc(), token.str, parser->str[parser->i]);
			parser->i++;
		}
	}
	token.type = get_token_type(token.str, lexer, 0);
	parser->i++;
	return (token);
}

t_token	consume_word(t_parser *parser, t_lexer *lexer)
{
	int		is_op;
	t_token	token;

	is_op = is_operator(parser->str[parser->i]);
	token.str = gc_strdup(get_gc(), "");
	while (parser->str[parser->i] && !ft_isspace(parser->str[parser->i])
		&& is_op == is_operator(parser->str[parser->i]))
	{
		if (parser->str[parser->i] == '\'')
			token_append(consume_single_quotes(parser, lexer), &token);
		else if (parser->str[parser->i] == '"')
			token_append(consume_double_quotes(parser, lexer), &token);
		else if (parser->str[parser->i] == '$')
			handle_dollar_sign(parser, lexer, 1, &token);
		else
		{
			token.str = gc_strappend(get_gc(),
					token.str, parser->str[parser->i]);
			parser->i++;
		}
	}
	token.type = get_token_type(token.str, lexer, 1);
	return (token);
}

static void	token_append(t_token new, t_token *token)
{
	token->str = gc_strjoin(get_gc(), token->str, new.str, 1);
	gc_free(get_gc(), new.str);
}
