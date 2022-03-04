/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 14:54:11 by cybattis          #+#    #+#             */
/*   Updated: 2022/03/04 16:42:20 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int redirection(t_redir *redirections)
{
	int	i;

	i = 0;
	// while (redirections[i])
	// {

	// 	i++;
	// }
	return (0);
}

int	redir_in(t_redir *redirections)
{
	int	fdin;

	fdin = open(redirections->file, O_RDONLY, 0666);
	if (fdin == -1)
		return (ft_errno(errno));
	dup2(fdin, STDIN_FILENO);
	close(fdin);
	return (0);
}

int	redir_out(t_redir *redirections)
{
	int	fdout;

	fdout = open(redirections->file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fdout == -1)
		return (ft_errno(errno));
	dup2(fdout, STDOUT_FILENO);
	close(fdout);
	return (0);
}

int	redi_out_append(t_redir *redirections)
{
	int	fdout;

	fdout = open(redirections->file, O_WRONLY | O_APPEND);
	if (fdout == -1)
		return (ft_errno(errno));
	dup2(fdout, STDOUT_FILENO);
	close(fdout);
	return (0);
}
