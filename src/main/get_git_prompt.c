/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_git_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:51:19 by cybattis          #+#    #+#             */
/*   Updated: 2022/03/27 14:23:13 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "core.h"
#include <sys/stat.h>
#include <fcntl.h>

static char	*trim_branch(char *str);
static char	*get_last_folders(char *path_to_git, char *full_path);
static char	*get_git_branch(char *path);

char	*get_git_prompt(char *path_to_git, char *current_path)
{
	char	*prompt;
	char	*folder;
	char	*git_branch;

	folder = get_last_folders(path_to_git, current_path);
	git_branch = get_git_branch(path_to_git);
	prompt = gc_strjoin(get_gc(), "\e[1;93mMinishell\e[0m: \e[1;94m",
			folder, 0);
	prompt = gc_strjoin(get_gc(), prompt, " \e[1;92mgit:(\e[1;91m", 1);
	prompt = gc_strjoin(get_gc(), prompt, git_branch, FREE_BOTH);
	prompt = gc_strjoin(get_gc(), prompt, "\e[1;92m)\e[0;m", 1);
	prompt = gc_strappend(get_gc(), prompt, '$');
	prompt = gc_strappend(get_gc(), prompt, ' ');
	gc_free(get_gc(), path_to_git);
	return (prompt);
}

int	is_git_repo(char *path)
{
	char		*full_path;
	struct stat	s;

	full_path = gc_strjoin(get_gc(), path, "/.git", 0);
	ft_memset(&s, 0, sizeof (struct stat));
	if (stat(full_path, &s) == 0)
	{
		gc_free(get_gc(), full_path);
		return (1);
	}
	gc_free(get_gc(), full_path);
	return (0);
}

static char	*get_last_folders(char *path_to_git, char *full_path)
{
	size_t	i;

	i = 0;
	while (path_to_git[i] && path_to_git[i] == full_path[i])
		i++;
	i--;
	while (i && full_path[i] == '/')
		i--;
	while (i && full_path[i] != '/')
		i--;
	i++;
	ft_memmove(full_path, full_path + i, ft_strlen(full_path + i) + 1);
	return (full_path);
}

static char	*get_git_branch(char *path)
{
	char	*branch;
	char	*full_path;
	int		fd;

	full_path = gc_strjoin(get_gc(), path, "/.git/HEAD", 0);
	fd = open(full_path, O_RDONLY);
	if (!fd)
	{
		gc_free(get_gc(), full_path);
		return (gc_strdup(get_gc(), "Unknown"));
	}
	branch = gc_get_next_line(get_gc(), fd);
	gc_free(get_gc(), full_path);
	close(fd);
	if (!branch)
		return ("unknown");
	branch = trim_branch(branch);
	return (branch);
}

static char	*trim_branch(char *str)
{
	char	*offset;

	offset = ft_strnstr(str, "heads/", ft_strlen(str));
	if (offset == NULL)
	{
		gc_free(get_gc(), str);
		return (gc_strdup(get_gc(), "Unknown"));
	}
	ft_memmove(str, offset + 6, ft_strlen(offset + 6) + 1);
	return (ft_trimr(str));
}
