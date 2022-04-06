/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:10:07 by cybattis          #+#    #+#             */
/*   Updated: 2022/04/06 13:15:19 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "core.h"
#include <errno.h>
#include <sys/wait.h>
#include <string.h>

static int	execute(t_command *command);
int			wait_for_child(pid_t pid);

int	execute_command(t_command_batch batch)
{
	t_pipe	*pipes;
	int		std_fds[2];

	if (batch.count == 0)
		return (0);
	dup_stdfds(std_fds);
	if (batch.commands[0].is_piping == 1)
	{
		g_minishell.is_piping = 1;
		pipes = init_pipe(batch.count);
		execute_pipe(&batch, pipes);
		gc_free(get_gc(), pipes);
		g_minishell.is_piping = 0;
	}
	else
		execute(&batch.commands[0]);
	restore_stdfds(std_fds);
	return (0);
}

static int	execute(t_command *command)
{
	pid_t	pid;

	if (command->is_redirecting && redirection(command->redirections) == -2)
		return (-1);
	if (!command[0].name)
		return (0);
	if (command->is_builtin == 1)
		return (execute_builtin(command));
	g_minishell.is_executing = 1;
	signal(SIGQUIT, sig_handler);
	pid = fork();
	if (!pid)
	{
		g_minishell.has_child = 1;
		execute_bin(command);
	}
	else if (pid > 0)
		return (wait_for_child(pid));
	g_minishell.is_executing = 0;
	return (ft_print_errno());
}

void	execute_bin(t_command *command)
{
	char	**path;
	char	*cmd_path;
	int		j;

	if (ft_strlen(command->name) == 0)
		ft_error_command("");
	if (ft_strchr(command->name, '/'))
	{
		execve(command->name, command->args, g_minishell.env);
		ft_errno_exit_msg(command->name, 126);
	}
	j = 0;
	path = get_path();
	while (path != NULL && path[j])
	{
		cmd_path = gc_strappend(get_gc(), path[j], '/');
		cmd_path = gc_strjoin(get_gc(), cmd_path, command->name, FREE_FIRST);
		if (execve(cmd_path, command->args, g_minishell.env) < 0
			&& errno != ENOENT)
			ft_errno_exit_msg(command->name, 126);
		j++;
	}
	ft_error_command(command->name);
}

char	**get_path(void)
{
	char	*path;

	path = get_env("PATH");
	if (!path)
		return (NULL);
	return (gc_split(get_gc(), path, ':'));
}
