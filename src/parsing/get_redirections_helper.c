#include "libft.h"
#include "parsing.h"

int	get_redir_type(char *str)
{
	size_t	size;

	size = 0;
	while (is_redirection_char(str[size]))
		size++;
	if (ft_strncmp(str, "<", size) == 0)
		return (TOKEN_REDIR_IN);
	if (ft_strncmp(str, "<<", size) == 0)
		return (TOKEN_REDIR_HEREDOC);
	if (ft_strncmp(str, ">", size) == 0)
		return (TOKEN_REDIR_OUT);
	if (ft_strncmp(str, ">>", size) == 0)
		return (TOKEN_REDIR_OUT_APPEND);
	return (TOKEN_UNKNOWN);
}

int	is_redirection(char *str)
{
	size_t	size;

	size = 0;
	while (is_redirection_char(str[size]))
		size++;
	if (!size)
		return (0);
	if (!ft_strncmp(str, "<", size) || !ft_strncmp(str, "<<", size)
		|| !ft_strncmp(str, ">", size) || !ft_strncmp(str, ">>", size))
		return (1);
	return (0);
}

int	is_redirection_char(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}
