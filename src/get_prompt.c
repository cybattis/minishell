/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:22:09 by njennes           #+#    #+#             */
/*   Updated: 2022/02/22 19:38:57 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/minishell.h"
#include <sys/param.h>
#include <sys/stat.h>
#include <fcntl.h>

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

char	*find_git_repo(char *current_path)
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
		return (NULL);
	return (path_to_repo);
}

char	*get_last_folders(char *path_to_git, char *full_path)
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

char	*trim_branch(char *str)
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

char	*get_git_branch(char *path)
{
	char	*branch;
	char	*full_path;
	int		fd;

	full_path = gc_strjoin(get_gc(), path, "/.git/HEAD", 0);
	fd = open(full_path, O_RDONLY);
	if (!fd)
		return (gc_strdup(get_gc(), "Unknown"));
	branch = gc_get_next_line(get_gc(), fd);
	gc_free(get_gc(), full_path);
	close(fd);
	branch = trim_branch(branch);
	return (branch);
}

char	*get_git_prompt(char *path_to_git, char *current_path)
{
	char	*prompt;
	char	*folder;
	char	*git_branch;

	folder = get_last_folders(path_to_git, current_path);
	git_branch = get_git_branch(path_to_git);
	prompt = gc_strjoin(get_gc(), "\e[1;93mMinishell\e[0m: \e[1;94m", folder, 0);
	prompt = gc_strjoin(get_gc(), prompt, " \e[1;92mgit:(\e[1;91m", 1);
	prompt = gc_strjoin(get_gc(), prompt, git_branch, 3);
	prompt = gc_strjoin(get_gc(), prompt, "\e[1;92m)\e[0;m", 1);
	prompt = gc_strappend(get_gc(), prompt, '$');
	prompt = gc_strappend(get_gc(), prompt, ' ');
	gc_free(get_gc(), path_to_git);
	return (prompt);
}

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
	prompt = gc_strjoin(get_gc(), "\e[1;93mMinishell\e[0m: \e[1;94m", buf, 0);
	prompt = gc_strjoin(get_gc(), prompt, "\e[0m", 1);
	prompt = gc_strappend(get_gc(), prompt, '$');
	prompt = gc_strappend(get_gc(), prompt, ' ');
	return (prompt);
}
