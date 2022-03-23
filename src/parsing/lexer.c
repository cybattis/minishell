#include "parsing.h"

void	lexer_add_token(t_lexer *lexer, t_token token)
{
	t_token	*new_ptr;

	new_ptr = gc_calloc(get_gc(), lexer->count + 1, sizeof (t_token));
	if (lexer->tokens)
	{
		ft_memmove(new_ptr, lexer->tokens, lexer->count * sizeof (t_token));
		gc_free(get_gc(), lexer->tokens);
	}
	lexer->tokens = new_ptr;
	lexer->tokens[lexer->count] = token;
	lexer->count++;
}

void	lexer_add_end(t_lexer *lexer)
{
	lexer_add_token(lexer, (t_token){TOKEN_END, NULL});
}
