/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:46:20 by njennes           #+#    #+#             */
/*   Updated: 2022/03/05 14:18:51 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include "minishell.h"

void	skip_spaces(t_parser *parser)
{
	while (parser->str[parser->i] == ' ')
		parser->i++;
}

void	lexer_add_token(t_token new_token, t_lexer *lexer)
{
	t_token	*new_ptr;

	new_ptr = gc_calloc(get_gc(), lexer->count + 1, sizeof (t_token));
	ft_memmove(new_ptr, lexer->tokens, lexer->count * sizeof (t_token));
	gc_free(get_gc(), lexer->tokens);
	lexer->tokens = new_ptr;
	lexer->tokens[lexer->count] = new_token;
	lexer->count = lexer->count + 1;
}

void	lexer_add_end(t_lexer *lexer)
{
	t_token	token;

	token.type = TOKEN_END;
	token.str = NULL;
	token.is_one_word = 1;
	lexer_add_token(token, lexer);
}

int	get_last_token_type(t_lexer *lexer)
{
	if (lexer->count == 0)
		return (TOKEN_EMPTY);
	return (lexer->tokens[lexer->count - 1].type);
}

char	*parse_env_name(t_parser *parser)
{
	size_t	start;
	char	*name;

	start = parser->i;
	while (parser->str[parser->i] && is_envchar(parser->str[parser->i]))
		parser->i++;
	name = gc_substr(get_gc(), parser->str, start, parser->i - start);
	return (name);
}

void	handle_env_value(t_lexer *lexer, char *value)
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

void	handle_dollar_sign(t_parser *parser, t_lexer *lexer)
{
	t_token	token;
	char	*env_name;
	char	*env_value;

	parser->i++;
	if (!is_envchar(parser->str[parser->i]))
	{
		if (parser->str[parser->i] == '?')
		{
			token.str = gc_itoa(get_gc(), g_minishell.last_return);
			token.type = get_token_type(token.str, lexer, 0);
			token.is_one_word = 1;
			lexer_add_token(token, lexer);
			parser->i++;
			return ;
		}
		token.str = gc_strdup(get_gc(), "$");
		token.type = get_token_type(token.str, lexer, 0);
		token.is_one_word = 1;
		lexer_add_token(token, lexer);
		parser->i++;
		return ;
	}
	env_name = parse_env_name(parser);
	env_value = getenv(env_name);
	gc_free(get_gc(), env_name);
	handle_env_value(lexer, env_value);
}

void	get_next_token(t_parser *parser, t_lexer *lexer)
{
	skip_spaces(parser);
	if (parser->str[parser->i] == '$')
		handle_dollar_sign(parser, lexer);
	else if (parser->str[parser->i] != '\0')
		lexer_add_token(consume_word(parser, lexer), lexer);
	else
		lexer_add_end(lexer);
}

t_lexer	tokenize_input(char *input)
{
	t_lexer		lexer;
	t_parser	parser;

	ft_memset(&lexer, 0, sizeof (t_lexer));
	parser.i = 0;
	parser.str = input;
	while (get_last_token_type(&lexer) != TOKEN_END)
	{
		get_next_token(&parser, &lexer);
	}
	return (lexer);
}

void	lexer_destroy(t_lexer *lexer)
{
	gc_free(get_gc(), lexer->tokens);
	lexer->tokens = NULL;
	lexer->count = 0;
}

char	*token_type_to_str(int token_type)
{
	if (token_type == TOKEN_UNKNOWN)
		return ("TOKEN_UNKNOWN");
	if (token_type == TOKEN_REDIR_OUT_APPEND)
		return ("TOKEN_REDIR_OUT_APPEND");
	if (token_type == TOKEN_REDIR_OUT)
		return ("TOKEN_REDIR_OUT");
	if (token_type == TOKEN_ARG)
		return ("TOKEN_ARG");
	if (token_type == TOKEN_COMMAND)
		return ("TOKEN_COMMAND");
	if (token_type == TOKEN_REDIR_RDOC)
		return ("TOKEN_REDIR_RDOC");
	if (token_type == TOKEN_REDIR_IN)
		return ("TOKEN_REDIR_IN");
	if (token_type == TOKEN_EMPTY)
		return ("TOKEN_EMPTY");
	if (token_type == TOKEN_PIPE)
		return ("TOKEN_PIPE");
	if (token_type == TOKEN_END)
		return ("TOKEN_END");
	if (token_type == TOKEN_FILE)
		return ("TOKEN_FILE");
	return ("NOT_A_TOKEN");
}

void	lexer_print(t_lexer *lexer)
{
	size_t	i;

	ft_printf("Lexer: size %d\n", (int)lexer->count);
	i = 0;
	while (i < lexer->count)
	{
		printf("Token[%d]: %s: -%s-\n", (int)i, token_type_to_str(lexer->tokens[i].type), lexer->tokens[i].str);
		i++;
	}
}
