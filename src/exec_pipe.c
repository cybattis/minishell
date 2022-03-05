/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:10:07 by cybattis          #+#    #+#             */
/*   Updated: 2022/03/05 15:33:38 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char	**environ;

int	execute_pipe(int *fds, t_command *command)
{
	pid_t	pid;
	int		status;

	pipe(fds);
	status = 0;
	pid = fork();
	if (!pid)
	{
		dup2(fds[1], STDOUT_FILENO);
		close(fds[0]);
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
		g_minishell.last_return = WIFEXITED(status);
	}
	else
		gc_callback(NULL);
	return (0);
}

// TODO: RDOC
// TODO: fix child return
