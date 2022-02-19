/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:10:07 by cybattis          #+#    #+#             */
/*   Updated: 2022/02/19 17:57:34 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_builtin(t_command_batch cmd_batch, size_t i);
static int	execute_extern(t_command_batch cmd_batch, size_t i);

int	execute_cmd(t_command_batch cmd_batch)
{
	size_t	i;

	i = 0;
	while (i < cmd_batch.count)
	{
		if (cmd_batch.commands[i].is_builtin == 1)
			execute_builtin(cmd_batch, i);
		else
			execute_extern(cmd_batch, i);
		i++;
	}
	return (0);
}

static int	execute_builtin(t_command_batch cmd_batch, size_t i)
{
	if (!ft_strcmp(cmd_batch.commands[i].name, "exit"))
		bt_exit();
	else if (!ft_strcmp(cmd_batch.commands[i].name, "cd"))
		bt_cd(cmd_batch.commands[i].args[1]);
	else if (!ft_strcmp(cmd_batch.commands[i].name, "echo"))
		bt_echo(cmd_batch.commands[i]);
	else if (!ft_strcmp(cmd_batch.commands[i].name, "pwd"))
		bt_pwd();
	return (0);
}

static int	execute_extern(t_command_batch cmd_batch, size_t i)
{
	pid_t	pid;
	int		status;

	i = 0;
	status = 0;
	pid = fork();
	if (!pid)
	{
		printf("cmd:%s args:%s\n", cmd_batch.commands[i].name, cmd_batch.commands[i].args[i]);
		if (!execve(cmd_batch.commands[i].name, ft_strjoin("./cat", cmd_batch.commands[i].args, 0), NULL))
			ft_errno_exit(errno);
	}
	else if (pid > 0)
	{
		pid = wait(&status);
		if (!WIFEXITED(status))
			ft_errno_exit(errno);
	}
	else
		ft_errno_exit(errno);
	return (0);
}
