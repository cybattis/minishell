/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 11:35:17 by cybattis          #+#    #+#             */
/*   Updated: 2022/03/21 16:12:25 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
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
			if (!ft_strcmp(redirections.file, buff))
				break;
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

static char *generate_file_name(void)
{
	int id;
	char *temp_file;

	id = 0;
	temp_file = gc_strdup(get_gc(), "/tmp/sh-thc-420-blaze");
	while (!access(temp_file, F_OK))
	{
		free(temp_file);
		temp_file = gc_strdup(get_gc(), "/tmp/sh-thc-");
		temp_file = gc_strjoin(get_gc(), temp_file, gc_itoa(get_gc(), id), FREE_SECOND);
		id++;
	}
	return (temp_file);
}

static int	generate_temp_file(char *str_out)
{
	int		fd_temp;
	char	*temp_file;

	temp_file = generate_file_name();
	fd_temp = open(temp_file,
			O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
	if (fd_temp == -1)
	{
		ft_print_errno();
		return (-1);
	}
	write(fd_temp, str_out, ft_strlen(str_out));
	close(fd_temp);
	gc_free(get_gc(), str_out);
	fd_temp = open(temp_file, O_RDONLY);
	unlink(temp_file);
	return (fd_temp);
}
