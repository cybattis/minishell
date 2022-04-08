/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 12:36:16 by cybattis          #+#    #+#             */
/*   Updated: 2022/04/08 14:21:12 by cybattis         ###   ########.fr       */
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
	g_minishell.is_heredoc = 0;
	if (!line_read)
		exit_minishell();
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
