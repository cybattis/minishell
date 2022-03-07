/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <cybattis@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:46:20 by njennes           #+#    #+#             */
/*   Updated: 2022/03/05 14:18:51 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include "minishell.h"

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
	token.str = gc_strdup(get_gc(), "newline");
	lexer_add_token(token, lexer);
}

int	get_last_token_type(t_lexer *lexer)
{
	if (lexer->count == 0)
		return (TOKEN_EMPTY);
	return (lexer->tokens[lexer->count - 1].type);
}

void	lexer_destroy(t_lexer *lexer)
{
	gc_free(get_gc(), lexer->tokens);
	lexer->tokens = NULL;
	lexer->count = 0;
}
