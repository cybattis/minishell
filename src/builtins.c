/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 15:04:11 by cybattis          #+#    #+#             */
/*   Updated: 2022/03/04 16:22:28 by cybattis         ###   ########.fr       */
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

// TODO: add arg return value + error if more than one arg
int	bt_exit(void)
{
	printf("exit\n");
	gc_clean(get_gc());
	exit(EXIT_SUCCESS);
	return (1);
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
	char	buf[MAXPATHLEN];

	if (!path || path[0] == '~')
		path = getenv("HOME");
	if (path && chdir(path))
		perror(strerror(errno));
	set_env_var("OLDPWD", getenv("PWD"));
	set_env_var("PWD", getcwd(buf, MAXPATHLEN));
	return (0);
}
