/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:10:07 by cybattis          #+#    #+#             */
/*   Updated: 2022/03/12 18:06:47 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "minishell.h"
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

extern char	**environ;

static void	execute_pipe_child(t_command *command, int *pipe_fds, int *pipe_next);

int	execute_pipe(t_command_batch *batch)
{
	size_t 	i;
	pid_t	pid;
	int		pipe_current[2];
	int		pipe_next[2];
	int		wstatus;

	i = 0;
	g_minishell.is_executing = 1;
	pipe(pipe_current);
	while (i < batch->count - 1)
	{
		pid = fork();
		pipe(pipe_next);
		if (!pid)
			execute_pipe_child(&batch->commands[i], pipe_current, pipe_next);
		i++;
	}
	if (pid > 0)
	{
		dup2(pipe_current[0], STDIN_FILENO);
		close(pipe_current[1]);
		while (i > 0)
		{
			wstatus = 0;
			waitpid(pid, &wstatus, 0);
			if (WIFEXITED(wstatus))
				g_minishell.last_return = WEXITSTATUS(wstatus);
			g_minishell.is_executing = 0;
			i--;
		}
		return (0);
	}
	return (gc_callback(NULL));
}

static void	execute_pipe_child(t_command *command, int *pipe_fds, int *pipe_next)
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
