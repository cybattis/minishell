/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:10:07 by cybattis          #+#    #+#             */
/*   Updated: 2022/02/17 18:18:31 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	launch_program(char *cmd, char *const *args)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (!pid)
	{
		if (execve(cmd, args, NULL) != 0)
			exit(EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	else if (pid > 0)
	{
		pid = wait(&status);
		if (!WIFEXITED(status))
		{
			printf("%s\n", strerror(errno));
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
