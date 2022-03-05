/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:10:07 by cybattis          #+#    #+#             */
/*   Updated: 2022/03/05 15:24:18 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "minishell.h"
#include <errno.h>
#include <sys/wait.h>

extern char	**environ;

static void	clean_fds(int save_fd[2]);
static int	execute_extern(t_command *command);

int	execute_command(t_command_batch cmd_batch)
{
	int		save_fd[2];
	int 	fds[2];
	size_t	i;

	i = 0;
	save_fd[0] = dup(STDIN_FILENO);
	save_fd[1] = dup(STDOUT_FILENO);
	while (i < cmd_batch.count)
	{
		if (cmd_batch.commands[i].is_redirecting == 1)
			if (redirection(cmd_batch.commands[i].redirections) && i >= 1)
				clean_fds(fds);
		if (cmd_batch.commands[i].is_piping == 1)
			execute_pipe(fds, &cmd_batch.commands[i]);
		else
		{
			if (cmd_batch.commands[i].is_builtin == 1)
				execute_builtin(&cmd_batch.commands[i]);
			else
				execute_extern(&cmd_batch.commands[i]);
			if (cmd_batch.commands[i].is_redirecting == 1 || (i >= 1 &&
				cmd_batch.commands[i - 1].is_piping == 1))
				clean_fds(save_fd);
		}
		i++;
	}
	return (0);
}

static void	clean_fds(int save_fd[2])
{
	if (dup2(save_fd[1], STDOUT_FILENO) < 0)
		ft_errno_exit(errno);
	if (dup2(save_fd[0], STDIN_FILENO) < 0)
		ft_errno_exit(errno);
	close(save_fd[0]);
	close(save_fd[1]);
}

static int	execute_extern(t_command *command)
{
	pid_t	pid;
	int		wait_status;

	wait_status = 0;
	pid = fork();
	if (!pid)
		execute_bin(command);
	else if (pid > 0)
	{
		pid = wait(&wait_status);
		g_minishell.last_return = WIFEXITED(wait_status);
	}
	else
		gc_callback(NULL);
	return (0);
}

void	execute_bin(t_command *command)
{
	char	**path;
	char	*cmd_path;
	int		j;

	path = get_path();
	j = 0;
	execve(command->name, command->args, environ);
	while (path[j])
	{
		cmd_path = gc_strappend(&g_minishell.gc, path[j], '/');
		cmd_path = gc_strjoin(&g_minishell.gc, cmd_path, command->name, 1);
		if (execve(cmd_path, command->args, environ) < 0 && errno != ENOENT)
			ft_errno_exit(errno);
		j++;
	}
	ft_error_command(command->args[0]);
}

char	**get_path(void)
{
	char	*path;

	path = getenv("PATH");
	if (!path)
		return (NULL);
	return (gc_split(&g_minishell.gc, path, ':'));
}
