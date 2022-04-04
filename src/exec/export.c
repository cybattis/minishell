/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 13:48:19 by cybattis          #+#    #+#             */
/*   Updated: 2022/04/04 16:46:41 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parsing.h"
#include "minishell.h"
#include "core.h"

static void	check_env(char **best_env, char *last_best, size_t i, size_t j);

static int	check_var(char *var)
{
	size_t	i;

	i = 0;
	if (var[0] == '=' || ft_isdigit(var[0]))
		return (0);
	while (var[i] && var[i] != '=')
	{
		if (!is_envchar(var[i]) && var[i] != '=')
			return (0);
		i++;
	}
	return (1);
}

static void	print_best_env(char *env)
{
	char	*value;
	char	*equals;

	env = gc_strdup(get_gc(), env);
	equals = ft_strchr(env, '=');
	ft_dprintf(STDERR_FILENO, "var: %s, equal: %p\n", env, equals);
	if (!equals)
		;//printf("declare -x %s\n", env);
	else
	{
		*equals = 0;
		value = gc_strdup(get_gc(), equals + 1);
		//printf("declare -x %s=\"%s\"\n", env, value);
		gc_free(get_gc(), value);
	}
	gc_free(get_gc(), env);
}

int	noarg_export(void)
{
	char	*last_best;
	char	*best_env;
	size_t	i;
	size_t	j;

	j = 0;
	best_env = g_minishell.env[j];
	while (g_minishell.env[j])
	{
		i = 0;
		if (!ft_strlen(g_minishell.env[j]))
		{
			j++;
			continue ;
		}
		last_best = best_env;
		while (g_minishell.env[i])
		{
			check_env(&best_env, last_best, i, j);
			i++;
		}
		print_best_env(best_env);
		j++;
	}
	return (0);
}

static void	check_env(char **best_env, char *last_best, size_t i, size_t j)
{
	if (ft_strcmp(g_minishell.env[i], *best_env) < 0
		&& (j == 0 || ft_strcmp(g_minishell.env[i], last_best) > 0))
		*best_env = g_minishell.env[i];
	else if (j > 0 && ft_strcmp(*best_env, last_best) <= 0)
		*best_env = g_minishell.env[i];
}

int	bt_export(char **arg)
{
	size_t	value_offset;
	size_t	i;

	i = 0;
	if (!arg[0])
		return (noarg_export());
	while (arg[i])
	{
		if (!check_var(arg[i]))
		{
			ft_dprintf(STDERR_FILENO, "minishell: export: `%s':"
				" not a valid identifier\n", arg[i++]);
			continue ;
		}
		value_offset = 0;
		while (arg[i][value_offset] && arg[i][value_offset] != '=')
			value_offset++;
		if (arg[i][value_offset] == '=')
		{
			arg[i][value_offset++] = 0;
			set_env_var(arg[i], &arg[i][value_offset]);
		}
		else
			set_env_var(arg[i], NULL);
		i++;
	}
	return (0);
}
