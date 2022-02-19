/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 15:04:11 by cybattis          #+#    #+#             */
/*   Updated: 2022/02/19 17:14:10 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bt_echo(char *str, char *args)
{
	if (args[1] == 'n')
		printf("%s", str);
	else
		printf("%s\n", str);
	return (0);
}

int	bt_exit(void)
{
	printf("exit\n");
	exit(EXIT_SUCCESS);
	return (0);
}

int	bt_pwd(void)
{
	char	buf[MAXPATHLEN];

	getcwd(buf, MAXPATHLEN);
	printf("%s\n", buf);
	return (0);
}

int	bt_cd(char *path)
{
	if (chdir(path))
		ft_errno_exit(errno);
	return (0);
}
