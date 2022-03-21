/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:10:07 by cybattis          #+#    #+#             */
/*   Updated: 2022/03/21 16:01:38 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

extern char	**environ;

static void	fork_pipe(t_command_batch *batch, t_pipe *pipes);

int	execute_pipe(t_command_batch *batch, t_pipe *pipes)
{
	size_t i;
	pid_t pid;
	int wstatus;

	i = 0;
	pid = 0;
	g_minishell.is_executing = 1;
	fork_pipe(batch, pipes);
	if (pid > 0)
	{
		wstatus = 0;
		dup2(pipes[0].fd[0], STDIN_FILENO);
		close(pipes[0].fd[0]);
		while (i > 0)
		{
			waitpid(pid, &wstatus, 0);
			g_minishell.last_return = WEXITSTATUS(wstatus);
			i--;
		}
		g_minishell.is_executing = 0;
		return (0);
	}
	return (ft_print_errno());
}

static void	fork_pipe(t_command_batch *batch, t_pipe *pipes)
{
	size_t	i;
	pid_t	pid;

	i = 0;
	pid = 0;
	while (pid >= 0 && i < batch->count)
	{
		pipe(pipes[i].fd);
		pid = fork();
		if (!pid)
		{
			if (redirection(batch->commands[i].redirections) <= 1)
			{
				dup2(pipes[i].fd[1], STDOUT_FILENO);
				close(pipes[i].fd[0]);
			}
			else
			{
				close(pipes[i].fd[1]);
				close(pipes[i].fd[0]);
			}
			if (batch->commands[i].is_builtin == 1)
				exit(execute_builtin(&batch->commands[i]));
			execute_bin(&batch->commands[i]);
		}
		i++;
	}
}

t_pipe	*init_pipe(size_t nbr)
{
	t_pipe	*pipes;

	pipes = gc_calloc(get_gc(), nbr, sizeof(t_pipe));
	if (!pipes)
		return (NULL);
	return (pipes);
}
