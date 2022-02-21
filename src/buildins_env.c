/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 13:48:19 by cybattis          #+#    #+#             */
/*   Updated: 2022/02/21 14:27:51 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
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

int	bt_export(char *var)
{
	int	i;

	i = 0;
	while (environ[i])
	{
		if (environ[i][0] == 0)
		{
			environ[i] = ft_strdup(var);
			return (0);
		}
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
			environ[i] = 0;
			return (0);
		}
		i++;
	}
	return (1);
}
