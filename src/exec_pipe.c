/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:10:07 by cybattis          #+#    #+#             */
/*   Updated: 2022/03/17 17:49:58 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

extern char	**environ;

static void	execute_pipe_child(t_command *command, int *pipe_fds, size_t i);

int	execute_pipe(t_command_batch *batch)
{
	size_t i;
	pid_t pid;
	int pipe_fd[2];
	int wstatus;

	i = 0;
	pid = 0;
	g_minishell.is_executing = 1;
	pipe(pipe_fd);
	while (pid >= 0 && i < batch->count)
	{
		pid = fork();
		if (!pid)
			execute_pipe_child(&batch->commands[i], pipe_fd, i);
		i++;
	}
	if (pid > 0)
	{
		wstatus = 0;
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		while (i > 0)
		{
			waitpid(pid, &wstatus, 0);
			g_minishell.last_return = WEXITSTATUS(wstatus);
			i--;
		}
		g_minishell.is_executing = 0;
	}
	else
		return (gc_callback(NULL));
	return (0);
}

static void	execute_pipe_child(t_command *command, int *pipe_fds, size_t i)
{
	if (i > 0)
	{
		dup2(pipe_fds[0], STDIN_FILENO);
		close(pipe_fds[1]);
	}
	if (redirection(command->redirections) <= 1)
	{
		dup2(pipe_fds[1], STDOUT_FILENO);
		close(pipe_fds[0]);
	}
	else
	{
		close(pipe_fds[1]);
		close(pipe_fds[0]);
	}
	if (command->is_builtin == 1)
		exit(execute_builtin(command));
//	if (errno == SIGPIPE)
//		exit(EXIT_FAILURE);
	execute_bin(command);
}
