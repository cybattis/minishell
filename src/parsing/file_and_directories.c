/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_and_directories.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 13:35:59 by njennes           #+#    #+#             */
/*   Updated: 2022/03/27 13:36:00 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/param.h>
#include "parsing.h"
#include "core.h"
#include "libft.h"

int	is_valid_path(char *str)
{
	struct stat	s;
	int			result;

	result = stat(str, &s);
	if (result)
		return (0);
	if (S_ISDIR(s.st_mode))
		return (PATH_DIRECTORY);
	return (PATH_FILE);
}

int	is_absolute_path(char *str)
{
	if (str[0] == '/')
		return (1);
	return (0);
}

void	make_absolute_path(char **str)
{
	char	pwd[MAXPATHLEN];

	getcwd(pwd, MAXPATHLEN);
	*str = gc_strjoin(get_gc(), "/", *str, FREE_SECOND);
	*str = gc_strjoin(get_gc(), pwd, *str, FREE_SECOND);
}

int	contains_file(char *str)
{
	char	*back_slash;

	back_slash = ft_strrchr(str, '/');
	if (!back_slash)
		return (1);
	if (back_slash[1])
		return (1);
	return (0);
}
