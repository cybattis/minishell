/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 13:48:19 by cybattis          #+#    #+#             */
/*   Updated: 2022/02/21 18:18:27 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include <stdio.h>

extern char	**environ;

int	bt_env(void)
{
	int	i;

	i = 0;
	while (environ[i])
	{
		if (environ[i][0] != 0)
			printf("%s\n", environ[i]);
		i++;
	}
	return (0);
}

static int	check_var(char *var)
{
	size_t	i;

	i = 0;
	if (ft_isdigit(var[0]))
		return (0);
	while (var[i] && var[i] != '=')
	{
		if (!is_envchar(var[i]) && var[i] != '=')
			return (0);
		i++;
	}
	return (1);
}

int	bt_export(char **args)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (args[i])
	{
		if (!check_var(args[i]))
		{
			i++;
			printf("%s\n", args[i]);
			continue ;
		}
		while (environ[j])
		{
			if (environ[j][0] == 0)
			{
				environ[j] = gc_strdup(&g_gc, args[i]);
				return (0);
			}
			j++;
		}
		environ = gc_strarray_append(&g_gc, environ, args[i]);
		i++;
	}
	return (0);
}

int	bt_unset(char *var)
{
	int	i;

	i = 0;
	while (environ[i])
	{
		if (!ft_strncmp(environ[i], var, ft_strlen(var)))
		{
			environ[i][0] = 0;
			return (0);
		}
		i++;
	}
	return (1);
}
