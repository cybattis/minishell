/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:10:07 by cybattis          #+#    #+#             */
/*   Updated: 2022/02/21 19:03:57 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <errno.h>
#include <sys/wait.h>

extern char	**environ;

static void	execute_bin(t_command *commands);
static int	execute_builtin(t_command *commands);
static int	execute_extern(t_command *commands);
static char	**get_path(void);

int	execute_command(t_command_batch cmd_batch)
{
	size_t	i;

	i = 0;
	while (i < cmd_batch.count)
	{
		if (cmd_batch.commands[i].is_builtin == 1)
			execute_builtin(&cmd_batch.commands[i]);
		else
			execute_extern(&cmd_batch.commands[i]);
		i++;
	}
	return (0);
}

static int	execute_builtin(t_command *commands)
{
	if (!ft_strcmp(commands->name, "cd"))
		bt_cd(commands->args[1]);
	else if (!ft_strcmp(commands->name, "echo"))
		bt_echo(commands);
	else if (!ft_strcmp(commands->name, "pwd"))
		bt_pwd();
	else if (!ft_strcmp(commands->name, "unset"))
		bt_unset(commands->args[1]);
	else if (!ft_strcmp(commands->name, "env"))
		bt_env();
	else if (!ft_strcmp(commands->name, "export"))
		bt_export(commands->args);
	else if (!ft_strcmp(commands->name, "exit"))
		bt_exit();
	return (0);
}

static int	execute_extern(t_command *commands)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (!pid)
		execute_bin(commands);
	else if (pid > 0)
	{
		pid = wait(&status);
		if (!WIFEXITED(status))
			gc_callback(NULL);
	}
	else
		gc_callback(NULL);
	return (0);
}

static void	execute_bin(t_command *commands)
{
	char	**path;
	char	*cmd_path;
	int		j;

	path = get_path();
	j = 0;
	execve(commands->name, commands->args, environ);
	while (path[j])
	{
		cmd_path = gc_strappend(&g_gc, path[j], '/');
		cmd_path = gc_strjoin(&g_gc, cmd_path, commands->name, 1);
		execve(cmd_path, commands->args, environ);
		j++;
	}
	ft_error_command(commands->args[0]);
}

static char	**get_path(void)
{
	char	*path;

	path = getenv("PATH");
	if (!path)
		return (NULL);
	return (gc_split(&g_gc, path, ':'));
}
