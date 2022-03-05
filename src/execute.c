/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:10:07 by cybattis          #+#    #+#             */
/*   Updated: 2022/03/05 14:54:40 by cybattis         ###   ########.fr       */
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
	int		save_fd[2];
	int 	fds[2];
	size_t	i;

	i = 0;
	save_fd[0] = dup(STDIN_FILENO);
	save_fd[1] = dup(STDOUT_FILENO);
	while (i < cmd_batch.count)
	{
		if (cmd_batch.commands[i].is_redirecting == 1)
			redirection(cmd_batch.commands[i].redirections);
		if (cmd_batch.commands[i].is_piping == 1)
		{
			pipe(fds);
			execute_pipe(fds, &cmd_batch.commands[i]);
		}
		else
		{
			if (cmd_batch.commands[i].is_builtin == 1)
				execute_builtin(&cmd_batch.commands[i]);
			else
				execute_extern(&cmd_batch.commands[i]);
			if (cmd_batch.commands[i].is_redirecting == 1 || ( i >= 1 &&
				cmd_batch.commands[i - 1].is_piping == 1))
			{
				dup2(save_fd[1], STDOUT_FILENO);
				dup2(save_fd[0], STDIN_FILENO);
				close(save_fd[0]);
				close(save_fd[1]);
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
