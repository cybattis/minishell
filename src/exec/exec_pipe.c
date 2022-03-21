/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:10:07 by cybattis          #+#    #+#             */
/*   Updated: 2022/03/20 12:58:33 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

extern char	**environ;

static void	execute_pipe_child(t_command *command, int *pipe_prev, int *pipe_next, size_t i);

int	execute_pipe(t_command_batch *batch)
{
	size_t i;
	pid_t pid;
	int pipe_prev[2];
	int pipe_next[2];
	int wstatus;

	i = 0;
	pid = 0;
	g_minishell.is_executing = 1;
	pipe(pipe_next);
	while (pid >= 0 && i < batch->count)
	{
		if (i > 0 && i < batch->count - 1)
		{
			pipe_prev[0] = pipe_next[0];
			pipe_prev[1] = pipe_next[1];
			pipe(pipe_next);
		}
		pid = fork();
		if (!pid)
			execute_pipe_child(&batch->commands[i], pipe_prev, pipe_next, i);
		i++;
	}
	if (pid > 0)
	{
		wstatus = 0;
		close(pipe_prev[0]);
		close(pipe_prev[1]);
		if (batch->count > 2)
		{
			close(pipe_next[0]);
			close(pipe_next[1]);
		}
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

static void	execute_pipe_child(t_command *command, int *pipe_prev, int *pipe_next, size_t i)
{
	if (i > 0)
	{
		dup2(pipe_prev[0], STDIN_FILENO);
		close(pipe_prev[1]);
	}
	if (redirection(command->redirections) <= 1)
	{
		dup2(pipe_next[1], STDOUT_FILENO);
		close(pipe_next[0]);
	}
	else
	{
		close(pipe_prev[1]);
		close(pipe_prev[0]);
	}
	if (command->is_builtin == 1)
		exit(execute_builtin(command));
	execute_bin(command);
}
