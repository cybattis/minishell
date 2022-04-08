/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:44:46 by cybattis          #+#    #+#             */
/*   Updated: 2022/04/07 17:45:17 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "minishell.h"

int	launch_heredoc(t_command_batch *batch)
{
	int		heredoc_fd;
	size_t	i;
	size_t	j;

	i = 0;
	heredoc_fd = 0;
	while (i < batch->count)
	{
		j = 0;
		while (batch->commands[i].redirections[j].type)
		{
			if (j > 0 && batch->commands[i].redirections[j - 1].heredoc_fd)
			{
				close(batch->commands[i].redirections[j - 1].heredoc_fd);
				batch->commands[i].redirections[j - 1].heredoc_fd = 0;
			}
			if (batch->commands[i].redirections[j].type == TOKEN_REDIR_HEREDOC)
				heredoc_fd = redir_heredoc(batch->commands[i].redirections[j]);
			if (heredoc_fd == SIGINT_HEREDOC)
				return (SIGINT_HEREDOC);
			batch->commands[i].redirections[j++].heredoc_fd = heredoc_fd;
		}
		i++;
	}
	return (0);
}

void	flush_readline(void)
{
	rl_pending_input = '\n';
	readline("");
}
