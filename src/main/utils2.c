/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 14:55:35 by cybattis          #+#    #+#             */
/*   Updated: 2022/03/30 18:03:58 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_arglen(char const **args)
{
	size_t	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
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
	if (fds[0] == -1 || fds[1] == -1)
	{
		close(fds[0]);
		close(fds[1]);
		return (-1);
	}
	return (0);
}
