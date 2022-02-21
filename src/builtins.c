/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 15:04:11 by cybattis          #+#    #+#             */
/*   Updated: 2022/02/21 20:23:10 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>
#include <errno.h>
#include <term.h>
#include <sys/param.h>

int	bt_echo(t_command *cmd)
{
	size_t	size;
	size_t	i;

	i = 1;
	size = ft_arglen((char const **)cmd->args);
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (i < size - 1)
			printf(" ");
		i++;
	}
	if (ft_strcmp(cmd->args[1], "-n"))
		printf("\n");
	return (0);
}

int	bt_exit(void)
{
	printf("exit\n");
	gc_clean(&g_minishell.gc);
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
	if (!path)
		path = getenv("USER");
	if (path && chdir(path))
		perror(strerror(errno));
	return (0);
}
