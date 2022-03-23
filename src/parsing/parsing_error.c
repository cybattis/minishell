#include "parsing.h"

char	*error_ambiguous_redirection(char *str)
{
	t_err_or_charptr	redir;

	redir = get_next_word(str, 0);
	printf("minishell: %s: ambiguous redirect\n", redir.result);
	return (NULL);
}

char	*parsing_error(char *str)
{
	printf("%s\n", str);
	return (NULL);
}

char	*file_error(char *str, char *file)
{
	printf("minishell: %s: %s\n", file, str);
	return (NULL);
}