/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 13:36:20 by njennes           #+#    #+#             */
/*   Updated: 2022/03/27 13:36:21 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	syntax_error(t_err error)
{
	char	*next_token;

	next_token = skip_spaces(error.error);
	if (*next_token)
	{
		ft_dprintf(STDERR_FILENO,
				"minishell: syntax error near unexpected token `%c'\n",
				*next_token);
	}
	else
	{
		ft_dprintf(STDERR_FILENO,
				"minishell: syntax error near unexpected token `%s'\n",
				"newline");
	}
	return (error.code);
}