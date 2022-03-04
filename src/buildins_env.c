/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 13:48:19 by cybattis          #+#    #+#             */
/*   Updated: 2022/03/04 16:34:26 by cybattis         ###   ########.fr       */
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
	size_t	value_offset;
	size_t	i;

	i = 0;
	while (args[i])
	{
		if (!check_var(args[i]))
		{
			printf("minishell: export: `%s': not a valid identifier\n", args[i]);
			i++;
			continue ;
		}
		value_offset = 0;
		while (args[i][value_offset] && args[i][value_offset] != '=')
			value_offset++;
		if (args[i][value_offset])
		{
			args[i][value_offset] = 0;
			value_offset++;
		}
		set_env_var(args[i], &args[i][value_offset]);
		i++;
	}
	return (0);
}

int	bt_unset(char **args)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (!is_envchar(args[i][j]))
				break ;
			j++;
		}
		if (args[i][j])
		{
			printf("minishell: unset: `%s': not a valid identifier\n", args[i]);
			i++;
			continue ;
		}
		unset_env_var(args[i]);
		i++;
	}
	return (1);
}
