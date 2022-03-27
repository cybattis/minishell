/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 13:48:19 by cybattis          #+#    #+#             */
/*   Updated: 2022/03/25 18:18:05 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parsing.h"
#include "minishell.h"

extern char	**environ;

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

char	**init_sort_env(size_t *max)
{
	size_t	i;
	char	**sort_env;

	i = 0;
	while (environ[i])
		i++;
	*max = i;
	sort_env = malloc(sizeof(char *) * (*max + 1));
	if (!sort_env)
		return (NULL);
	sort_env[0] = 0;
	return (sort_env);
}

int is_env_sort(char *best_env, char *sort_env, size_t i, size_t j)
{
	size_t	k;

	k = 0;
	while (k < j)
	{
		if (ft_strcmp(&sort_env[k], environ[i]) == 0)
			break;
		k++;
	}
	if (k == j && ft_strcmp(&sort_env[k], environ[i]) != 0)
		best_env = environ[i];
	return (1);
	//TODO: finish that
}

int noarg_export(void)
{
	char	**sort_env;
	char	*best_env;
	size_t	i;
	size_t	j;
	size_t	max;

	sort_env = init_sort_env(&max);
	j = 0;
	while (j < max)
	{
		i = 0;
		best_env = environ[i];
		while (environ[i])
		{
			if (ft_strcmp(best_env, environ[i]) > 0)
				is_env_sort(best_env, environ[i], i, j);
			i++;
		}
		sort_env[j] = ft_strdup(best_env);
		sort_env[j + 1] = 0;
		printf("declare -x %s\n", sort_env[j]);
		j++;
	}
	// print_sort_env();
	return (0);
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
									  " not a valid identifier\n", arg[i]);
			i++;
			continue ;
		}
		value_offset = 0;
		while (arg[i][value_offset] && arg[i][value_offset] != '=')
			value_offset++;
		if (arg[i][value_offset])
		{
			arg[i][value_offset] = 0;
			value_offset++;
		}
		else
		{
			i++;
			continue ;
		}
		set_env_var(arg[i], &arg[i][value_offset]);
		i++;
	}
	return (0);
}
