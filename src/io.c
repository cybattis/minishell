/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 12:36:16 by cybattis          #+#    #+#             */
/*   Updated: 2022/02/22 18:01:37 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "readline.h"
#include "minishell.h"

char	*ft_get_line(void)
{
	static char	*line_read;

	if (line_read)
		gc_free(get_gc(), line_read);
	line_read = readline(get_prompt());
	if (!line_read)
	{
		rl_replace_line("exit", 1);
		gc_clean(get_gc());
		exit(EXIT_SUCCESS);
	}
	if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}
