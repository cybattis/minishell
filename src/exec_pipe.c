/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:10:07 by cybattis          #+#    #+#             */
/*   Updated: 2022/03/04 14:00:30 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

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
		dup2(fds[1], STDOUT_FILENO);
		close(fds[0]);
		close(fds[1]);
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
		close(fds[0]);
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

int redirection(t_command *command)
{
	if (command->redirection_file && command->redirection_type == TOKEN_REDIR_OUT)
	{
		int	fdout;

		fdout = open(command->redirection_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (fdout == -1)
			return (ft_errno(errno));
		dup2(fdout, STDOUT_FILENO);
		close(fdout);
		return (0);
	}
	if (command->redirection_file && command->redirection_type == TOKEN_REDIR_IN)
	{
		int fdin;

		fdin = open(command->redirection_file, O_RDONLY, 0666);
		if (fdin == -1)
			return (ft_errno(errno));
		dup2(fdin, STDIN_FILENO);
		close(fdin);
		return (0);
	}
	if (command->redirection_file && command->redirection_type == TOKEN_REDIR_OUT_APPEND)
	{
		int fdout;

		fdout = open(command->redirection_file, O_WRONLY | O_APPEND);
		if (fdout == -1)
			return (ft_errno(errno));
		dup2(fdout, STDOUT_FILENO);
		close(fdout);
		return (0);
	}
	// TODO: RDOC
	return (0);
}
