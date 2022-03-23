/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:10:07 by cybattis          #+#    #+#             */
/*   Updated: 2022/03/23 18:26:22 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <sys/wait.h>
#include <string.h>

extern char	**environ;

static int	execute(t_command *command);

int	execute_command(t_command_batch batch)
{
	t_pipe	*pipes;
	int		save_fd[2];

	save_fd[0] = dup(STDIN_FILENO);
	save_fd[1] = dup(STDOUT_FILENO);
	if (batch.count == 0)
		return (0);
	if (batch.commands[0].is_piping == 1)
	{
		pipes = init_pipe(batch.count);
		execute_pipe(&batch, pipes);
		gc_free(get_gc(), pipes);
	}
	else
		execute(&batch.commands[0]);
	clean_fds(save_fd);
	return (0);
}

static int	execute(t_command *command)
{
	pid_t	pid;
	int		wstatus;

	if (command->is_redirecting)
		redirection(command->redirections);
	if (command->is_builtin == 1)
		return (execute_builtin(command));
	wstatus = 0;
	g_minishell.is_executing = 1;
	pid = fork();
	if (!pid)
		execute_bin(command);
	else if (pid > 0)
	{
		waitpid(pid, &wstatus, 0);
		g_minishell.last_return = WEXITSTATUS(wstatus);
		g_minishell.is_executing = 0;
		return (0);
	}
	return (ft_print_errno());
}

void	execute_bin(t_command *command)
{
	char	**path;
	char	*cmd_path;
	int		j;

	path = get_path();
	j = 0;
	if (execve(command->name, command->args, environ) < 0 && errno != ENOENT)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s\n", strerror(errno));
		exit(126);
	}
	while (path[j])
	{
		cmd_path = gc_strappend(&g_minishell.gc, path[j], '/');
		cmd_path = gc_strjoin(&g_minishell.gc, cmd_path, command->name, 1);
		if (execve(cmd_path, command->args, environ) < 0 && errno != ENOENT)
		{
			ft_dprintf(STDERR_FILENO, "minishell: %s\n", strerror(errno));
			exit(126);
		}
		j++;
	}

	ft_error_command(command->name);
}

int	clean_fds(int save_fd[2])
{
	if (dup2(save_fd[1], STDOUT_FILENO) < 0)
		ft_print_errno();
	if (dup2(save_fd[0], STDIN_FILENO) < 0)
		ft_print_errno();
	close(save_fd[0]);
	close(save_fd[1]);
	return (1);
}

char	**get_path(void)
{
	char	*path;

	path = getenv("PATH");
	if (!path)
		return (NULL);
	return (gc_split(&g_minishell.gc, path, ':'));
}
