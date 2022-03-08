/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 11:35:17 by cybattis          #+#    #+#             */
/*   Updated: 2022/03/08 11:53:39 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <errno.h>
#include "minishell.h"

static int	generate_temp_file(char *str_out);

int	redir_heredoc(t_redir redirections)
{
	char	*str_out;
	char	*buff;
	char	c;

	str_out = gc_strdup(get_gc(), "");
	buff = gc_strdup(get_gc(), "");
	ft_printf("> ");
	while (read(STDIN_FILENO, &c, 1) > 0)
	{
		if (c == '\n')
		{
			if (!ft_strcmp(buff, redirections.file))
				break ;
			buff = gc_strappend(get_gc(), buff, c);
			str_out = gc_strjoin(get_gc(), str_out, buff, FREE_BOTH);
			buff = gc_strdup(get_gc(), "");
			ft_printf("> ");
		}
		else
			buff = gc_strappend(get_gc(), buff, c);
	}
	gc_free(get_gc(), buff);
	return (generate_temp_file(str_out));
}

static int	generate_temp_file(char *str_out)
{
	int		fd_temp;
	char	*temp_file;

	temp_file = gc_strdup(get_gc(), "/tmp/sh-thd-123456");
	fd_temp = open(temp_file,
			O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
	if (fd_temp == -1)
		return (-ft_errno(errno));
	write(fd_temp, str_out, ft_strlen(str_out));
	close(fd_temp);
	gc_free(get_gc(), str_out);
	fd_temp = open(temp_file, O_RDONLY);
	unlink("/tmp/sh-thd-123456");
	return (fd_temp);
}
