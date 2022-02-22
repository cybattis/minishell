/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 14:55:35 by cybattis          #+#    #+#             */
/*   Updated: 2022/02/21 20:21:57 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

t_gc	*get_gc()
{
	return (&g_minishell.gc);
}

void	ft_errno_exit(int errnum)
{
	printf("%s\n", strerror(errnum));
	exit(EXIT_FAILURE);
}

void	ft_error_command(char *command)
{
	printf("minishell: %s : command not found\n", command);
	exit(EXIT_FAILURE);
}

size_t	ft_arglen(char const **args)
{
	size_t	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	gc_callback(void *ptr)
{
	(void)ptr;
	gc_clean(&g_minishell.gc);
	ft_errno_exit(errno);
	return (0);
}
