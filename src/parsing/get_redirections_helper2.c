/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirections_helper2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 13:50:23 by njennes           #+#    #+#             */
/*   Updated: 2022/03/27 13:50:24 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "core.h"

static size_t	get_redir_count(char *str);
int				is_redirection(char *str);

int	allocate_redirs(t_command *command, char *str)
{
	size_t	redir_count;

	redir_count = get_redir_count(str);
	if (redir_count)
		command->is_redirecting = 1;
	command->redirections = gc_calloc(get_gc(),
			redir_count + 1, sizeof (t_redir));
	if (!redir_count)
		return (0);
	return (1);
}

size_t	skip_redir_chars(char *str, size_t i)
{
	while (str[i] == '>' || str[i] == '<')
		i++;
	return (i);
}

size_t	get_to_next_char(char *str, size_t i)
{
	if (str[i])
		i++;
	return (i);
}

static size_t	get_redir_count(char *str)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i] && str[i] != '|')
	{
		if (is_redirection(&str[i]))
			count++;
		while (str[i] == '>' || str[i] == '<')
			i++;
		if (str[i] == '\'' || str[i] == '"')
			i += skip_quotes(&str[i]);
		if (str[i])
			i++;
	}
	return (count);
}
