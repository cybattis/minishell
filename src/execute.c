/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:10:07 by cybattis          #+#    #+#             */
/*   Updated: 2022/02/19 15:29:54 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_cmd(t_command_batch cmd_batch)
{
	int		i;
	pid_t	pid;
	int		status;

	i = 0;
	status = 0;
	pid = fork();
	if (!pid)
	{
		while (i < cmd_batch.count)
		{
			if (!execve(&cmd_batch.commands[i], &cmd_batch.commands[i].args, NULL))
				ft_errno_exit(errno);
			i++;
		}
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
