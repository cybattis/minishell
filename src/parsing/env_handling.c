/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:46:20 by njennes           #+#    #+#             */
/*   Updated: 2022/03/08 12:30:15 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../libft/libft.h"
#include "../../includes/minishell.h"

static void	which_sign(t_parser *parser, t_token *token);
static void	handle_env_value(t_lexer *lexer, char *value);
static char	*parse_env_name(t_parser *parser);

t_token	handle_dollar_sign(t_parser *parser, t_lexer *lexer, int chop_tokens)
{
	t_token	token;
	char	*env_name;
	char	*env_value;

	parser->i++;
	ft_memset(&token, 0, sizeof(t_token));
	if (!is_envchar(parser->str[parser->i]))
	{
		which_sign(parser, &token);
		token.type = get_token_type(token.str, lexer, 0);
		if (chop_tokens)
			lexer_add_token(token, lexer);
		return (token);
	}
	env_name = parse_env_name(parser);
	env_value = getenv(env_name);
	gc_free(get_gc(), env_name);
	if (chop_tokens)
		handle_env_value(lexer, env_value);
	return (token);
}

static void	which_sign(t_parser *parser, t_token *token)
{
	if (parser->str[parser->i] == '?')
	{
		token->str = gc_itoa(get_gc(), g_minishell.last_return);
		parser->i++;
	}
	else
		token->str = gc_strdup(get_gc(), "$");
}

int	is_envchar(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

static void	handle_env_value(t_lexer *lexer, char *value)
{
	t_parser	value_parser;

	value_parser.i = 0;
	value_parser.str = value;
	while (value_parser.str[value_parser.i])
	{
		skip_spaces(&value_parser);
		if (value_parser.str[value_parser.i] == '\'')
			lexer_add_token(consume_single_quotes(&value_parser, lexer), lexer);
		else
			lexer_add_token(consume_word(&value_parser, lexer), lexer);
	}
}

static char	*parse_env_name(t_parser *parser)
{
	size_t	start;
	char	*name;

	start = parser->i;
	while (parser->str[parser->i] && is_envchar(parser->str[parser->i]))
		parser->i++;
	name = gc_substr(get_gc(), parser->str, start, parser->i - start);
	return (name);
}
