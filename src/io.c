/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 12:36:16 by cybattis          #+#    #+#             */
/*   Updated: 2022/02/18 15:48:42 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_line(void)
{
	static char	*line_read;

	if (line_read)
		free(line_read);
	line_read = readline(get_prompt());
	if (!line_read)
		exit(EXIT_SUCCESS);
	if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}

char	*get_prompt(void)
{
	return ("\e[1;93mMinishell:\e[0m$ ");
}
