/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:10:07 by cybattis          #+#    #+#             */
/*   Updated: 2022/03/03 17:04:14 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "minishell.h"
#include <errno.h>
#include <sys/wait.h>

extern char	**environ;

static int	execute_extern(t_command *command);

int	execute_command(t_command_batch cmd_batch)
{
	int		fd;
	int 	fds[2];
	size_t	i;

	i = 0;
	fd = 0;
	while (i < cmd_batch.count)
	{
		if (cmd_batch.commands[i].as_pipe == 1)
		{
			pipe(fds);
			execute_pipe(fds, &cmd_batch.commands[i]);
		}
		else
		{
			if (cmd_batch.commands[i].is_redirecting == 1)
				redirection(fd, &cmd_batch.commands[i]);
			if (cmd_batch.commands[i].is_builtin == 1)
				execute_builtin(&cmd_batch.commands[i]);
			else
				execute_extern(&cmd_batch.commands[i]);
			if (cmd_batch.commands[i].is_redirecting == 1)
			{
				dup2(fd, STDOUT_FILENO);
				close(fd);
			}
		}
		i++;
	}
	return (0);
}

int	execute_builtin(t_command *command)
{
	if (!ft_strcmp(command->name, "cd"))
		bt_cd(command->args[1]);
	else if (!ft_strcmp(command->name, "echo"))
		bt_echo(command);
	else if (!ft_strcmp(command->name, "pwd"))
		bt_pwd();
	else if (!ft_strcmp(command->name, "unset"))
		bt_unset(&command->args[1]);
	else if (!ft_strcmp(command->name, "env"))
		bt_env();
	else if (!ft_strcmp(command->name, "export"))
		bt_export(&command->args[1]);
	else if (!ft_strcmp(command->name, "exit"))
		bt_exit();
	return (0);
}

static int	execute_extern(t_command *command)
{
	int		child_ret;
	pid_t	pid;
	int		wait_status;

	wait_status = 0;
	pid = fork();
	if (!pid)
		execute_bin(command);
	else if (pid > 0)
	{
		pid = wait(&wait_status);
		child_ret = WIFEXITED(wait_status);
		g_minishell.local_env[0] = gc_itoa(&g_minishell.gc, child_ret);
		if (!child_ret)
			gc_callback(NULL);
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
