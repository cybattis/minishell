/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 11:35:17 by cybattis          #+#    #+#             */
/*   Updated: 2022/04/07 15:21:48 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "readline.h"
#include "minishell.h"
#include "core.h"

static int	generate_temp_file(char *str_out);
static int	is_heredoc_open(void);

int	redir_heredoc(t_redir redirections)
{
	char	*str_out;
	char	*buff;

	g_minishell.is_heredoc = 1;
	str_out = gc_strdup(get_gc(), "");
	buff = readline("> ");
	if (!is_heredoc_open())
		return (SIGINT_HEREDOC);
	while (buff)
	{
		if (ft_strlen(buff) == ft_strlen(redirections.file)
			&& !ft_strncmp(redirections.file, buff, ft_strlen(buff) - 1))
			break ;
		str_out = gc_strjoin(get_gc(), str_out, buff, FREE_BOTH);
		str_out = gc_strappend(get_gc(), str_out, '\n');
		free(buff);
		buff = readline("> ");
	}
	if (buff)
		free(buff);
	if (!is_heredoc_open())
		return (SIGINT_HEREDOC);
	g_minishell.is_heredoc = 0;
	return (generate_temp_file(str_out));
}

static int	is_heredoc_open(void)
{
	if (g_minishell.is_heredoc == SIGINT_HEREDOC)
	{
		g_minishell.is_heredoc = -1;
		return (0);
	}
	return (1);
}

static char	*generate_file_name(void)
{
	int		id;
	char	*temp_file;

	id = 0;
	temp_file = gc_strdup(get_gc(), "/tmp/sh-thd-0");
	while (!access(temp_file, F_OK))
	{
		free(temp_file);
		temp_file = gc_strdup(get_gc(), "/tmp/sh-thd-");
		temp_file = gc_strjoin(get_gc(), temp_file,
				gc_itoa(get_gc(), id), FREE_SECOND);
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
	fd_temp = open(temp_file, O_RDONLY);
	gc_free(get_gc(), str_out);
	unlink(temp_file);
	gc_free(get_gc(), temp_file);
	g_minishell.is_executing = 0;
	return (fd_temp);
}

int	close_heredoc(t_command_batch *batch)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < batch->count)
	{
		j = 0;
		while (batch->commands[i].redirections[j].type)
		{
			if (batch->commands[i].redirections[j].heredoc_fd > 0)
				close(batch->commands[i].redirections[j].heredoc_fd);
			j++;
		}
		i++;
	}
	return (0);
}
