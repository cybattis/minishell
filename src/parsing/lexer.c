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

#include "../../includes/parsing.h"
#include "../../libft/libft.h"

void	skip_spaces(t_parser *parser)
{
	while (parser->str[parser->i] == ' ')
		parser->i++;
}

void	lexer_add_token(t_token new_token, t_lexer *lexer)
{
	t_token	*new_ptr;

	new_ptr = ft_calloc(lexer->count + 1, sizeof (t_token)); //TODO: Replace this with gc_calloc
	ft_memmove(new_ptr, lexer->tokens, lexer->count * sizeof (t_token));
	free(lexer->tokens); //TODO: replace with gc_free
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

void	get_next_token(t_parser *parser, t_lexer *lexer)
{
	skip_spaces(parser);
	if (parser->str[parser->i] == '\'')
		consume_single_quotes(parser, lexer);
	else if (parser->str[parser->i] == '\"')
		consume_double_quotes(parser, lexer);
	else if (parser->str[parser->i] != '\0')
		consume_word(parser, lexer);
	else
		lexer_add_end(lexer);
}

t_lexer	tokenize_input(char *input)
{
	t_lexer		lexer;
	t_parser	parser;

	//TODO: Expand env vars before lexing
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
	free(lexer->tokens);
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
	if (token_type == TOKEN_REDIR_IN_APPEND)
		return ("TOKEN_REDIR_IN_APPEND");
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

	i = 0;
	while (i < lexer->count)
	{
		printf("Token[%d]: %s: -%s-\n", (int)i, token_type_to_str(lexer->tokens[i].type), lexer->tokens[i].str);
		i++;
	}
}
