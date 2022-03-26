#include "parsing.h"
#include "libft.h"

int	get_last_token_type(t_lexer *lexer)
{
	if (lexer->count == 0)
		return (TOKEN_EMPTY);
	return (lexer->tokens[lexer->count - 1].type);
}

int	get_token_type(char *token, t_lexer *lexer)
{
	int	last_token;

	last_token = get_last_token_type(lexer);
	if (last_token == TOKEN_EMPTY)
		return (TOKEN_COMMAND);
	else
		return (TOKEN_ARG);
}
