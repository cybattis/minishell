/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 14:55:35 by cybattis          #+#    #+#             */
/*   Updated: 2022/03/27 14:23:23 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "core.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void	ft_errno_exit(void)
{
	ft_dprintf(STDERR_FILENO, "minishell: %s\n", strerror(errno));
	exit(EXIT_FAILURE);
}

int	ft_print_errno(void)
{
	ft_dprintf(STDERR_FILENO, "minishell: %s\n", strerror(errno));
	return (1);
}

void	ft_error_command(char *command)
{
	ft_dprintf(STDERR_FILENO, "minishell: %s: command not found\n", command);
	exit(127);
}

void	ft_errno_exit_msg(char *name, int code)
{
	ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", name, strerror(errno));
	exit(code);
}

int	gc_callback(void *ptr)
{
	(void)ptr;
	gc_clean(&g_minishell.gc);
	ft_errno_exit();
	return (1);
}
