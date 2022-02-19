/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 15:04:11 by cybattis          #+#    #+#             */
/*   Updated: 2022/02/19 16:46:42 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bt_echo(char *str, char *args)
{
	if (args[1] == 'n')
		write(1, str, ft_strlen(str));
	else
	{
		write(1, str, ft_strlen(str));
		write(1, '\n', 1);
	}
	return (0);
}

int	bt_exit(void)
{
	write(1, "exit\n", 5);
	exit(EXIT_SUCCESS);
	return (0);
}

int	bt_pwd(void)
{
	char	buf[MAXPATHLEN];

	getcwd(buf, MAXPATHLEN);
	write(1, buf, ft_strlen(buf));
	return (0);
}

int	bt_cd(char *path)
{
	chdir(path);
	return (0);
}
