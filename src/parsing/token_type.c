#include "parsing.h"

int	get_last_token_type(t_lexer *lexer)
{
	if (lexer->count == 0)
		return (TOKEN_EMPTY);
	return (lexer->tokens[lexer->count - 1].type);
}

int	get_token_type(char *token, t_lexer *lexer)
{
	int	last_token;

	if (ft_strlen(token) <= 2)
	{
		if (ft_strcmp(token, "|") == 0)
			return (TOKEN_PIPE);
		if (ft_strcmp(token, ">") == 0)
			return (TOKEN_REDIR_OUT);
		if (ft_strcmp(token, "<") == 0)
			return (TOKEN_REDIR_IN);
		if (ft_strcmp(token, ">>") == 0)
			return (TOKEN_REDIR_OUT_APPEND);
		if (ft_strcmp(token, "<<") == 0)
			return (TOKEN_REDIR_HEREDOC);
	}
	last_token = get_last_token_type(lexer);
	if (last_token == TOKEN_EMPTY || last_token == TOKEN_PIPE
		|| last_token == TOKEN_FILE)
		return (TOKEN_COMMAND);
	if (last_token == TOKEN_COMMAND || last_token == TOKEN_ARG)
		return (TOKEN_ARG);
	if (last_token == TOKEN_REDIR_OUT || last_token == TOKEN_REDIR_OUT_APPEND
		|| last_token == TOKEN_REDIR_IN || last_token == TOKEN_REDIR_HEREDOC)
		return (TOKEN_FILE);
	return (TOKEN_UNKNOWN);
}
