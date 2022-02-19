/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:10:07 by cybattis          #+#    #+#             */
/*   Updated: 2022/02/19 11:10:06 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	launch_program(void)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (!pid)
	{
		// if (execve() != 0)
		// 	exit(EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	else if (pid > 0)
	{
		pid = wait(&status);
		if (!WIFEXITED(status))
		{
			perror(strerror(errno));
			return (0);
		}
	}
	else
	{
		printf("fork() failed!\n");
		return (0);
	}
	return (1);
}
