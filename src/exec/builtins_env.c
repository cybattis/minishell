/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 13:48:19 by cybattis          #+#    #+#             */
/*   Updated: 2022/03/05 15:48:07 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "core.h"
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

int	bt_export(char **arg)
{
	size_t	value_offset;
	size_t	i;

	i = 0;
	while (arg[i])
	{
		if (!check_var(arg[i]))
		{
			ft_dprintf(STDERR_FILENO, "minishell: export: `%s': not a valid identifier\n", arg[i]);
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
		set_env_var(arg[i], &arg[i][value_offset]);
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
			ft_dprintf(STDERR_FILENO, "minishell: unset: `%s': not a valid identifier\n", args[i]);
			i++;
			continue ;
		}
		unset_env_var(args[i]);
		i++;
	}
	return (1);
}
