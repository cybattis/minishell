/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:10:07 by cybattis          #+#    #+#             */
/*   Updated: 2022/04/07 15:58:19 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "core.h"
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

static int	pipe_redirection(size_t i, t_command_batch *batch, t_pipe *pipes);
static void	close_pipe(size_t max, t_pipe *pipes);
static int	fork_pipe(t_command_batch *batch, t_pipe *pipes);

int	execute_pipe(t_command_batch *batch, t_pipe *pipes)
{
	size_t	i;
	int		wstatus;

	i = 0;
	while (i < batch->count - 1)
		pipe(pipes[i++].fd);
	i = 0;
	if (launch_heredoc(batch) == SIGINT_HEREDOC)
		return (SIGINT_HEREDOC);
	wstatus = fork_pipe(batch, pipes);
	close_pipe(batch->count - 1, pipes);
	if (wstatus < 0)
	{
		g_minishell.is_executing = 0;
		return (1);
	}
	while (i < batch->count)
	{
		waitpid(-1, &wstatus, 0);
		get_child_return(wstatus);
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
		g_minishell.is_executing = 1;
		pid = fork();
		if (!pid)
		{
			pipe_redirection(i, batch, pipes);
			if (batch->commands[i].is_builtin == 1)
				exit(execute_builtin(&batch->commands[i]));
			execute_bin(&batch->commands[i]);
		}
		else if (pid < 0)
		{
			g_minishell.is_executing = 0;
			return (ft_print_errno());
		}
		i++;
	}
	return (0);
}

static int	pipe_redirection(size_t i, t_command_batch *batch, t_pipe *pipes)
{
	int	status;

	status = redirection(batch->commands[i].redirections);
	if (status > 0)
	{
		if (i > 0 && (status == ONLY_OUT || status == NO_FD_SET))
		{
			if (dup2(pipes[i - 1].fd[0], STDIN_FILENO) == -1)
				ft_print_errno();
		}
		if (i < batch->count - 1 && (status == ONLY_IN || status == NO_FD_SET))
		{
			if (dup2(pipes[i].fd[1], STDOUT_FILENO) == -1)
				ft_print_errno();
		}
		close_pipe(batch->count - 1, pipes);
		return (0);
	}
	close_pipe(batch->count - 1, pipes);
	if (status == -1)
		exit(1);
	return (-1);
}

t_pipe	*init_pipe(size_t nbr)
{
	t_pipe	*pipes;

	pipes = gc_calloc(get_gc(), nbr, sizeof(t_pipe));
	if (!pipes)
		return (NULL);
	return (pipes);
}

static void	close_pipe(size_t max, t_pipe *pipes)
{
	size_t	i;

	i = 0;
	while (i < max)
	{
		close(pipes[i].fd[0]);
		close(pipes[i].fd[1]);
		i++;
	}
}
