/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 14:54:11 by cybattis          #+#    #+#             */
/*   Updated: 2022/03/21 15:02:58 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <unistd.h>

static int	redir_in(int fd, t_redir redirections);
static int	redir_out(int fd, t_redir redirections);
static int	redir_out_append(int fd, t_redir redirections);
static int	set_redirection(int fds[2]);

int	redirection(t_redir *redirections)
{
	int	fds[2];
	int	i;

	i = 0;
	ft_memset(fds, 0, sizeof(int) * 2);
	while (redirections[i].type)
	{
		if (redirections[i].type == TOKEN_REDIR_IN)
			fds[0] = redir_in(fds[0], redirections[i]);
		else if (redirections[i].type == TOKEN_REDIR_HEREDOC)
			fds[0] = redir_heredoc(redirections[i]);
		else if (redirections[i].type == TOKEN_REDIR_OUT)
			fds[1] = redir_out(fds[1], redirections[i]);
		else if (redirections[i].type == TOKEN_REDIR_OUT_APPEND)
			fds[1] = redir_out_append(fds[1], redirections[i]);
		if (fds[0] == -1 || fds[1] == -1)
			return (-1);
		i++;
	}
	return (set_redirection(fds));
}

static int	set_redirection(int fds[2])
{
	if (fds[0])
	{
		if (dup2(fds[0], STDIN_FILENO) < 0)
		{
			ft_print_errno();
			return (-1);
		}
		close(fds[0]);
	}
	if (fds[1])
	{
		if (dup2(fds[1], STDOUT_FILENO) < 0)
		{
			ft_print_errno();
			return (-1);
		}
		close(fds[1]);
	}
	if (fds[1])
		return (fds[1]);
	return (-1);
}

static int	redir_in(int fd, t_redir redirections)
{
	if (fd)
		close(fd);
	fd = open(redirections.file, O_RDONLY, 0666);
	if (fd == -1)
		ft_print_errno();
	return (fd);
}

static int	redir_out(int fd, t_redir redirections)
{
	if (fd)
		close(fd);
	fd = open(redirections.file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
		ft_print_errno();
	return (fd);
}

static int	redir_out_append(int fd, t_redir redirections)
{
	if (fd)
		close(fd);
	fd = open(redirections.file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd == -1)
		return (ft_print_errno());
	return (fd);
}
