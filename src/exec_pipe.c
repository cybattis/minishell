/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:10:07 by cybattis          #+#    #+#             */
/*   Updated: 2022/03/16 16:41:32 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

extern char	**environ;

static void	execute_pipe_child(t_command *command, int *pipe_fds);

int	execute_pipe(t_command_batch *batch)
{
	size_t i;
	pid_t pid;
	int pipe_fd[2];
	int fd_in;
	int wstatus;

	i = 0;
	fd_in = 0;
	g_minishell.is_executing = 1;
	while (i < batch->count - 1)
	{
		pid = fork();
		pipe(pipe_fd);
		if (!pid)
		{
			dup2(fd_in, STDIN_FILENO);
			if (i < batch->count - 1)
				dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[0]);
			execute_pipe_child(&batch->commands[i], pipe_fd);
		}
		if (pid > 0)
		{
			wstatus = 0;
			waitpid(pid, &wstatus, 0);
			close(pipe_fd[1]);
			g_minishell.last_return = WEXITSTATUS(wstatus);
			g_minishell.is_executing = 0;
			fd_in = pipe_fd[0];
			i++;
		}
		else
			return (gc_callback(NULL));
	}
	return (0);
}

static void	execute_pipe_child(t_command *command, int *pipe_fds)
{
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
	execute_bin(command);
}
