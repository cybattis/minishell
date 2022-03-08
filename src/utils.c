/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 14:55:35 by cybattis          #+#    #+#             */
/*   Updated: 2022/03/05 15:57:10 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

t_gc	*get_gc(void)
{
	return (&g_minishell.gc);
}

void	ft_errno_exit(int errnum)
{
	printf("minishell: %s\n", strerror(errnum));
	exit(EXIT_FAILURE);
}

int	ft_errno(int errnum)
{
	printf("minishell: %s\n", strerror(errnum));
	return (1);
}

void	ft_error_command(char *command)
{
	printf("minishell: %s : command not found\n", command);
	exit(EXIT_FAILURE);
}

int	gc_callback(void *ptr)
{
	(void)ptr;
	gc_clean(&g_minishell.gc);
	ft_errno_exit(errno);
	return (1);
}
