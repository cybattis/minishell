/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 12:36:16 by cybattis          #+#    #+#             */
/*   Updated: 2022/03/05 16:36:53 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include "readline.h"
#include "minishell.h"
#include "core.h"

static int	write_to_prompt(char *msg);

char	*ft_get_line(void)
{
	static char	*line_read;

	if (line_read)
		gc_free(get_gc(), line_read);
	line_read = readline(get_prompt());
	if (!line_read)
		write_to_prompt("exit\n");
	if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}

static int	write_to_prompt(char *msg)
{
	int		fd;
	char	*tty_name;

	tty_name = ttyname(STDIN_FILENO);
	fd = open(tty_name, O_WRONLY);
	if (fd == -1)
		return (ft_print_errno());
	write(fd, msg, ft_strlen(msg));
	gc_clean(get_gc());
	exit(EXIT_SUCCESS);
	return (0);
}
