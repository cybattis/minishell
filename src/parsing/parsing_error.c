#include "parsing.h"
#include "libft.h"

char	*error_ambiguous_redirection(char *str)
{
	t_err_or_charptr	redir;

	redir = get_next_word(str, 0);
	ft_dprintf(STDERR_FILENO, "minishell: %s: ambiguous redirect\n", redir.result);
	return (NULL);
}

char	*parsing_error(char *str)
{
	ft_dprintf(STDERR_FILENO, "%s\n", str);
	return (NULL);
}

char	*file_error(char *str, char *file)
{
	ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", file, str);
	return (NULL);
}