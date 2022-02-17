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

int	consume_single_quotes(t_parser *parser, t_lexer *lexer)
{
	//TODO: implementation
}

int	consume_double_quotes(t_parser *parser, t_lexer *lexer)
{
	//TODO: implementation
}

int	consume_word(t_parser *parser, t_lexer *lexer)
{
	int		last_token;
	t_token	token;

	token.is_one_word = FT_TRUE;
	token.str = ft_substr(parser->str, parser->i,
							ft_word_size(&parser->str[parser->i])); //TODO: Replace with a new gc_substr
	last_token = get_last_token_type(lexer);
	//TODO: Figure out token type
}
