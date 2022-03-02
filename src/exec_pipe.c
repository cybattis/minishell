/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:10:07 by cybattis          #+#    #+#             */
/*   Updated: 2022/03/03 00:16:44 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

extern char	**environ;

int	execute_pipe(int *fds, t_command *command)
{
	pid_t	pid;
	int		child_ret;
	int		status;

	status = 0;
	pid = fork();
	if (!pid)
	{
		close(fds[0]);
		dup2(fds[1], STDOUT_FILENO);
		if (command->is_builtin == 1)
		{
			execute_builtin(command);
			exit(EXIT_SUCCESS);
		}
		execute_bin(command);
	}
	if (pid > 0)
	{
		dup2(fds[0], STDIN_FILENO);
		close(fds[1]);
		pid = wait(&status);
		child_ret = WIFEXITED(status);
		g_minishell.local_env[0] = gc_itoa(&g_minishell.gc, child_ret);
		if (!child_ret)
			gc_callback(NULL);
	}
	else
		gc_callback(NULL);
	return (0);
}
