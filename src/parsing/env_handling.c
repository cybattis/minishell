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
static void	chop_var(t_lexer *lexer, char *value, t_token *current);
static char	*parse_env_name(t_parser *parser);

void	handle_dollar_sign(t_parser *parser, t_lexer *lexer,
			int chop_tokens, t_token *current)
{
	char	*env_name;
	char	*env_value;

	parser->i++;
	if (!is_envchar(parser->str[parser->i]))
	{
		which_sign(parser, current);
		current->type = get_token_type(current->str, lexer, 0);
		return ;
	}
	env_name = parse_env_name(parser);
	env_value = getenv(env_name);
	gc_free(get_gc(), env_name);
	if (chop_tokens)
		chop_var(lexer, env_value, current);
	else
		current->str = gc_strjoin(get_gc(), current->str, env_value, FREE_FIRST);
}

static void	which_sign(t_parser *parser, t_token *token)
{
	if (parser->str[parser->i] == '?')
	{
		token->str = gc_strjoin(get_gc(), token->str,
					gc_itoa(get_gc(), g_minishell.last_return), FREE_BOTH);
		parser->i++;
	}
	else
		token->str = gc_strappend(get_gc(), token->str, '$');
}

int	is_envchar(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

static void	chop_var(t_lexer *lexer, char *value, t_token *current)
{
	t_token		token;
	t_parser	value_parser;
	int			pushed_current;

	value_parser.i = 0;
	value_parser.str = value;
	pushed_current = 0;
	if (skip_spaces(&value_parser))
	{
		lexer_add_token(*current, lexer);
		current->str = gc_strdup(get_gc(), "");
		pushed_current = 1;
	}
	while (value_parser.str[value_parser.i])
	{
		if (value_parser.str[value_parser.i] == '\'')
			token = consume_single_quotes(&value_parser, lexer);
		else
			token = consume_word(&value_parser, lexer);
		if (pushed_current)
			lexer_add_token(token, lexer);
		else
		{
			current->str = gc_strjoin(get_gc(), current->str, token.str, FREE_BOTH);
			if (skip_spaces(&value_parser))
			{
				lexer_add_token(*current, lexer);
				current->str = gc_strdup(get_gc(), "");
				pushed_current = 1;
			}
		}
		skip_spaces(&value_parser);
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
