/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:10:07 by cybattis          #+#    #+#             */
/*   Updated: 2022/03/23 14:08:45 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

extern char	**environ;

static int	pipe_redirection(size_t i, t_command_batch *batch, t_pipe *pipes);
static void	close_pipe(t_command_batch *batch, t_pipe *pipes);
static int	fork_pipe(t_command_batch *batch, t_pipe *pipes);

int	execute_pipe(t_command_batch *batch, t_pipe *pipes)
{
	size_t	i;
	int		wstatus;

	i = 0;
	g_minishell.is_executing = 1;
	if (fork_pipe(batch, pipes))
		return (1);
	wstatus = 0;
	close_pipe(batch, pipes);
	while (i < batch->count)
	{
		waitpid(-1, &wstatus, 0);
		g_minishell.last_return = WEXITSTATUS(wstatus);
		i++;
	}
	g_minishell.is_executing = 0;
	return (0);
}

static int	fork_pipe(t_command_batch *batch, t_pipe *pipes)
{
	size_t	i;
	pid_t	pid;

	i = 0;
	while (i < batch->count)
	{
		if (i < batch->count - 1)
			pipe(pipes[i].fd);
		pid = fork();
		if (!pid)
		{
			signal(SIGINT, SIG_DFL);
			pipe_redirection(i, batch, pipes);
			if (batch->commands[i].is_builtin == 1)
				exit(execute_builtin(&batch->commands[i]));
			execute_bin(&batch->commands[i]);
		}
		else if (pid < 0)
			return (ft_print_errno());
		pipes[i].pid = pid;
		i++;
	}
	return (0);
}

static int	pipe_redirection(size_t i, t_command_batch *batch, t_pipe *pipes)
{
	if (redirection(batch->commands[i].redirections) < 1)
	{
		if (i < batch->count - 1)
		{
			dup2(pipes[i].fd[1], STDOUT_FILENO);
			close(pipes[i].fd[0]);
		}
		if (i > 0)
		{
			dup2(pipes[i - 1].fd[0], STDIN_FILENO);
			close(pipes[i - 1].fd[1]);
		}
	}
	else
		close_pipe(batch, pipes);
	return (0);
}

t_pipe	*init_pipe(size_t nbr)
{
	t_pipe	*pipes;

	pipes = gc_calloc(get_gc(), nbr, sizeof(t_pipe));
	if (!pipes)
		return (NULL);
	return (pipes);
}

static void	close_pipe(t_command_batch *batch, t_pipe *pipes)
{
	size_t	i;

	i = 0;
	while (i < batch->count)
	{
		close(pipes[i].fd[0]);
		close(pipes[i].fd[1]);
		i++;
	}
}