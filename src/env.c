/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:46:20 by njennes           #+#    #+#             */
/*   Updated: 2022/03/27 14:23:21 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "core.h"
#include "minishell.h"
#include <unistd.h>

extern char	**environ;

static void	update_env_var(char *name, char *value);
static void	create_env_var(char *name, char *value);
static int	env_var_index(const char *name);

void	set_env_var(char *name, char *value)
{
	if (env_var_index(name) != -1)
		update_env_var(name, value);
	else
		create_env_var(name, value);
}

void	unset_env_var(char *name)
{
	int	i;

	i = env_var_index(name);
	if (i == -1)
		return ;
	environ[i][0] = 0;
}

static int	env_var_index(const char *name)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (environ[i])
	{
		if (environ[i][0] == 0)
		{
			i++;
			continue ;
		}
		j = 0;
		while (name[j] && name[j] == environ[i][j])
			j++;
		if (!name[j] && environ[i][j] == '=')
			return ((int)i);
		i++;
	}
	return (-1);
}

static void	update_env_var(char *name, char *value)
{
	size_t	i;

	i = env_var_index(name);
	gc_free(get_gc(), environ[i]);
	environ[i] = gc_strdup(get_gc(), name);
	environ[i] = gc_strappend(get_gc(), environ[i], '=');
	environ[i] = gc_strjoin(get_gc(), environ[i], value, 1);
}

static void	create_env_var(char *name, char *value)
{
	char	*new_entry;
	int		empty_index;

	new_entry = gc_strdup(get_gc(), name);
	new_entry = gc_strappend(get_gc(), new_entry, '=');
	new_entry = gc_strjoin(get_gc(), new_entry, value, 1);
	empty_index = get_empty_var_index();
	if (empty_index == -1)
		environ = gc_strarray_append(get_gc(), environ, new_entry);
	else
	{
		gc_free(get_gc(), environ[empty_index]);
		environ[empty_index] = gc_strdup(get_gc(), new_entry);
	}
	gc_free(get_gc(), new_entry);
}
