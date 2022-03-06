/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:10:07 by cybattis          #+#    #+#             */
/*   Updated: 2022/03/06 11:47:05 by cybattis         ###   ########.fr       */
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
	int		wstatus;

	pipe(fds);
	wstatus = 0;
	pid = fork();
	if (!pid)
	{
		dup2(fds[1], STDOUT_FILENO);
		close(fds[0]);
		if (command->is_builtin == 1)
			exit(execute_builtin(command));
		execute_bin(command);
	}
	if (pid > 0)
	{
		dup2(fds[0], STDIN_FILENO);
		close(fds[1]);
		waitpid(pid, &wstatus, 0);
		if (WIFEXITED(wstatus))
			g_minishell.last_return = WEXITSTATUS(wstatus);
		return (0);
	}
	return (gc_callback(NULL));
}

// TODO: RDOC
// TODO: fix child return
