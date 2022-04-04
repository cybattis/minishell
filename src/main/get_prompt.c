/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:22:09 by njennes           #+#    #+#             */
/*   Updated: 2022/03/27 14:23:14 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "core.h"
#include <sys/param.h>
#include <sys/stat.h>
#include <fcntl.h>

static char	*find_git_repo(char *current_path);

char	*get_prompt(void)
{
	char	*git_repo;
	char	*prompt;
	char	buf[MAXPATHLEN];

	getcwd(buf, MAXPATHLEN);
	git_repo = find_git_repo(buf);
	if (git_repo)
		return (get_git_prompt(git_repo, buf));
	else
		gc_free(get_gc(), git_repo);
	prompt = gc_strjoin(get_gc(), "\1\e[1;93m\2Minishell\1\e[0m\2: "
			"\1\e[1;94m\2", buf, 0);
	prompt = gc_strjoin(get_gc(), prompt, "\1\e[0m\2", 1);
	prompt = gc_strappend(get_gc(), prompt, '$');
	prompt = gc_strappend(get_gc(), prompt, ' ');
	return (prompt);
}

static char	*find_git_repo(char *current_path)
{
	size_t	i;
	char	*path_to_repo;

	path_to_repo = gc_strdup(get_gc(), current_path);
	while (ft_strlen(path_to_repo) && !is_git_repo(path_to_repo))
	{
		i = ft_strlen(path_to_repo);
		while (i && path_to_repo[i] != '/')
			i--;
		path_to_repo[i] = 0;
	}
	if (ft_strlen(path_to_repo) == 0)
	{
		gc_free(get_gc(), path_to_repo);
		return (NULL);
	}
	return (path_to_repo);
}
