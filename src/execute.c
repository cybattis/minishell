/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:10:07 by cybattis          #+#    #+#             */
/*   Updated: 2022/03/07 19:50:47 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <sys/wait.h>

extern char	**environ;

static int	execute(t_command *command);

int	execute_command(t_command_batch cmd_batch)
{
	int		save_fd[2];
	size_t	i;

	i = 0;
	save_fd[0] = dup(STDIN_FILENO);
	save_fd[1] = dup(STDOUT_FILENO);
	while (i < cmd_batch.count)
	{
		if (cmd_batch.commands[i].is_piping == 1)
			execute_pipe(&cmd_batch.commands[i]);
		else
		{
			execute(&cmd_batch.commands[i]);
			clean_fds(save_fd);
		}
		i++;
	}
	return (0);
}

int	clean_fds(int save_fd[2])
{
	if (dup2(save_fd[1], STDOUT_FILENO) < 0)
		ft_errno(errno);
	if (dup2(save_fd[0], STDIN_FILENO) < 0)
		ft_errno(errno);
	close(save_fd[0]);
	close(save_fd[1]);
	return (1);
}

static int	execute(t_command *command)
{
	pid_t	pid;
	int		wstatus;

	if (command->is_builtin == 1)
	{
		redirection(command->redirections);
		return (execute_builtin(command));
	}
	wstatus = 0;
	g_minishell.is_executing = 1;
	pid = fork();
	if (!pid)
	{
		redirection(command->redirections);
		execute_bin(command);
	}
	else if (pid > 0)
	{
		waitpid(pid, &wstatus, 0);
		if (WIFEXITED(wstatus))
			g_minishell.last_return = WEXITSTATUS(wstatus);
		g_minishell.is_executing = 0;
		return (0);
	}
	return (gc_callback(NULL));
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
