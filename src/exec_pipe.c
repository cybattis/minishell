/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:10:07 by cybattis          #+#    #+#             */
/*   Updated: 2022/03/08 11:50:30 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char	**environ;

void	execute_pipe_child(t_command *command, int *pipe_fds);

int	execute_pipe(t_command *command)
{
	pid_t	pid;
	int		pipe_fds[2];
	int		wstatus;

	g_minishell.is_executing = 1;
	pipe(pipe_fds);
	wstatus = 0;
	pid = fork();
	if (!pid)
		execute_pipe_child(command, pipe_fds);
	if (pid > 0)
	{
		dup2(pipe_fds[0], STDIN_FILENO);
		close(pipe_fds[1]);
		waitpid(pid, &wstatus, 0);
		if (WIFEXITED(wstatus))
			g_minishell.last_return = WEXITSTATUS(wstatus);
		g_minishell.is_executing = 0;
		return (0);
	}
	return (gc_callback(NULL));
}

void	execute_pipe_child(t_command *command, int *pipe_fds)
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
