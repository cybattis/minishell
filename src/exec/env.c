/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:46:20 by njennes           #+#    #+#             */
/*   Updated: 2022/04/04 15:50:55 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "core.h"
#include "minishell.h"
#include <unistd.h>

static void	update_env_var(char *name, char *value);
static void	create_env_var(char *name, char *value);
int			env_var_index(const char *name);

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
	g_minishell.env[i][0] = 0;
}

int	env_var_index(const char *name)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (g_minishell.env[i])
	{
		if (g_minishell.env[i][0] == 0)
		{
			i++;
			continue ;
		}
		j = 0;
		while (name[j] && name[j] == g_minishell.env[i][j])
			j++;
		if (!name[j] && g_minishell.env[i][j] == '=')
			return ((int)i);
		i++;
	}
	return (-1);
}

static void	update_env_var(char *name, char *value)
{
	size_t	i;

	i = env_var_index(name);
	gc_free(get_gc(), g_minishell.env[i]);
	g_minishell.env[i] = gc_strdup(get_gc(), name);
	g_minishell.env[i] = gc_strappend(get_gc(), g_minishell.env[i], '=');
	g_minishell.env[i] = gc_strjoin(get_gc(),
			g_minishell.env[i], value, FREE_FIRST);
}

static void	create_env_var(char *name, char *value)
{
	char	*new_entry;
	int		empty_index;

	new_entry = gc_strdup(get_gc(), name);
	new_entry = gc_strappend(get_gc(), new_entry, '=');
	new_entry = gc_strjoin(get_gc(), new_entry, value, FREE_FIRST);
	empty_index = get_empty_var_index();
	if (empty_index == -1)
		g_minishell.env = gc_strarray_append(get_gc(),
				g_minishell.env, new_entry);
	else
	{
		gc_free(get_gc(), g_minishell.env[empty_index]);
		g_minishell.env[empty_index] = gc_strdup(get_gc(), new_entry);
	}
	gc_free(get_gc(), new_entry);
}
