/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <cybattis@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:46:20 by njennes           #+#    #+#             */
/*   Updated: 2022/03/05 14:18:51 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../includes/parsing.h"
#include "../../includes/minishell.h"

static void	get_next_token(t_parser *parser, t_lexer *lexer);

t_lexer	tokenize_input(char *input)
{
	t_lexer		lexer;
	t_parser	parser;

	ft_memset(&lexer, 0, sizeof (t_lexer));
	parser.i = 0;
	parser.str = input;
	while (get_last_token_type(&lexer) != TOKEN_END)
		get_next_token(&parser, &lexer);
	return (lexer);
}

int	skip_spaces(t_parser *parser)
{
	int	skipped;

	skipped = 0;
	while (ft_isspace(parser->str[parser->i]))
	{
		parser->i++;
		skipped = 1;
	}
	return (skipped);
}

static void	get_next_token(t_parser *parser, t_lexer *lexer)
{
	skip_spaces(parser);
	if (parser->str[parser->i] != '\0')
		lexer_add_token(consume_word(parser, lexer), lexer);
	else
		lexer_add_end(lexer);
}
