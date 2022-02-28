/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:10:07 by cybattis          #+#    #+#             */
/*   Updated: 2022/02/28 16:44:42 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <sys/wait.h>

extern char	**environ;

static void	execute_bin(t_command *commands, int fd);
static int	execute_builtin(t_command *command);
static int	execute_extern(t_command *command);

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

static int	execute_builtin(t_command *command)
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
//    ssize_t	nbytes;
    int     fd[2];
	int		child_ret;
	pid_t	pid;
	int		wait_status;
    char    readbuffer[BUFSIZ];

	wait_status = 0;
	pid = fork();
    pipe(fd);
	if (!pid)           // child
        execute_bin(command, fd[0]);
	else if (pid > 0)   // parent
	{
        close(fd[1]);
        read(fd[0], readbuffer, BUFSIZ);
        dprintf(fd[0], "Received string: [%s]\n", readbuffer);
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

static void	execute_bin(t_command *commands, int fd)
{
	char	**path;
	char	*cmd_path;
	int		j;

    dup2(0, fd);
	path = get_path();
	j = 0;
	execve(commands->name, commands->args, environ);
	while (path[j])
	{
		cmd_path = gc_strappend(&g_minishell.gc, path[j], '/');
		cmd_path = gc_strjoin(&g_minishell.gc, cmd_path, commands->name, 1);
		if (execve(cmd_path, commands->args, environ) == -1 && errno != ENOENT)
			ft_errno_exit(errno);
		j++;
	}
	ft_error_command(commands->args[0]);
}

char	**get_path(void)
{
	char	*path;

	path = getenv("PATH");
	if (!path)
		return (NULL);
	return (gc_split(&g_minishell.gc, path, ':'));
}
