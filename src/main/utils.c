/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 14:55:35 by cybattis          #+#    #+#             */
/*   Updated: 2022/04/05 11:30:07 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "minishell.h"

t_gc	*get_gc(void)
{
	return (&g_minishell.gc);
}

int	ft_error_dup(int fd)
{
	if (fd == -1)
	{
		ft_print_errno();
		close(fd);
	}
	return (-1);
}

int	clean_redirection(int *fds)
{
	if (fds[0] <= -1 || fds[1] == -1)
	{
		close(fds[0]);
		close(fds[1]);
		if (fds[0] == SIGINT_HD)
			return (SIGINT_HD);
		return (-1);
	}
	return (0);
}

int	dup_stdfds(int std_fds[2])
{
	std_fds[0] = dup(STDIN_FILENO);
	std_fds[1] = dup(STDOUT_FILENO);
	return (0);
}

int	restore_stdfds(int std_fd[2])
{
	if (dup2(std_fd[1], STDOUT_FILENO) < 0)
		ft_print_errno();
	if (dup2(std_fd[0], STDIN_FILENO) < 0)
		ft_print_errno();
	close(std_fd[0]);
	close(std_fd[1]);
	return (0);
}
