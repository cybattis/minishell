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

void	lexer_add_token(int type, char *str, int is_one_word, t_lexer *lexer)
{
	t_token	new_token;
	t_token	*new_ptr;

	new_token.str = str;
	new_token.type = type;
	new_token.is_one_word = is_one_word;
	new_ptr = ft_calloc(lexer->count + 1, sizeof (t_token)); //TODO: Replace this with gc_calloc
	ft_memmove(new_ptr, lexer->tokens, lexer->count * sizeof (t_token));
	free(lexer->tokens); //TODO: replace with gc_free
	lexer->tokens = new_ptr;
	lexer->tokens[lexer->count] = new_token;
	lexer->count = lexer->count + 1;
}

void	lexer_add_end(t_lexer *lexer)
{
	lexer_add_token(TOKEN_END, NULL, 1, lexer);
}

int	get_last_token_type(t_lexer *lexer)
{
	if (lexer->count == 0)
		return (TOKEN_EMPTY);
	return (lexer->tokens[lexer->count].type);
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

	ft_memseti(&lexer, 0, sizeof (t_lexer));
	parser.i = 0;
	parser.str = input;
	while (get_last_token_type(&lexer) != TOKEN_END)
	{
		get_next_token(&parser, &lexer);
	}
	return (lexer);
}
