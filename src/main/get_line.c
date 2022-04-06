/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 12:36:16 by cybattis          #+#    #+#             */
/*   Updated: 2022/04/04 15:24:06 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "minishell.h"
#include "core.h"

static int	exit_minishell(void);

char	*ft_get_line(void)
{
	static char	*line_read = NULL;
	static char	*prompt = NULL;

	if (line_read)
		free(line_read);
	if (prompt)
		gc_free(get_gc(), prompt);
	prompt = get_prompt();
	line_read = readline(prompt);
	if (!line_read)
		exit_minishell();
	if (!ft_strlen(line_read))
		g_minishell.last_return = 0;
	if (line_read && *line_read && !contains_unfinished_quotes(line_read))
		add_history(line_read);
	return (gc_strdup(get_gc(), line_read));
}

static int	exit_minishell(void)
{
	ft_dprintf(STDERR_FILENO, "exit\n");
	gc_clean(get_gc());
	exit(EXIT_SUCCESS);
}
