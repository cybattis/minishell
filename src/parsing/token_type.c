#include "parsing.h"
#include "libft.h"

int	get_last_token_type(t_lexer *lexer)
{
	if (lexer->count == 0)
		return (TOKEN_EMPTY);
	return (lexer->tokens[lexer->count - 1].type);
}

int	get_token_type(char *token, t_lexer *lexer, t_parser parser)
{
	int	last_token;

	if (ft_strlen(token) == 0)
	{
		while (parser.str[parser.i] && !ft_isspace(parser.str[parser.i])
			&& parser.str[parser.i] != '"' && parser.str[parser.i] != '\'')
			parser.i++;
		if (!parser.str[parser.i] || ft_isspace(parser.str[parser.i]))
			return (TOKEN_EMPTY);
	}
	last_token = get_last_token_type(lexer);
	if (last_token == TOKEN_EMPTY)
		return (TOKEN_COMMAND);
	else
		return (TOKEN_ARG);
}
