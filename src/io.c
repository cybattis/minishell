/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 12:36:16 by cybattis          #+#    #+#             */
/*   Updated: 2022/02/21 14:06:35 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <sys/param.h>

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
	static char	*prompt;
	char		buf[MAXPATHLEN];

	if (prompt)
		free(prompt);
	getcwd(buf, MAXPATHLEN);
	prompt = ft_strjoin("\e[1;93mMinishell\e[0m: \e[1;94m", buf, 0);
	prompt = ft_strjoin(prompt, "\e[0m", 1);
	prompt = ft_strappend(prompt, '$');
	prompt = ft_strappend(prompt, ' ');
	return (prompt);
}
