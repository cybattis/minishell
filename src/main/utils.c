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

#include "minishell.h"

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
