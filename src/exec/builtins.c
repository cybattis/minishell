/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 15:04:11 by cybattis          #+#    #+#             */
/*   Updated: 2022/03/27 14:23:10 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "core.h"
#include <string.h>
#include <errno.h>
#include <sys/param.h>

int	execute_builtin(t_command *command)
{
	if (!command->name)
		return (0);
	g_minishell.is_executing = 1;
	if (!ft_strcmp(command->name, "cd"))
		g_minishell.last_return = bt_cd(command->args[1]);
	else if (!ft_strcmp(command->name, "echo"))
		g_minishell.last_return = bt_echo(command);
	else if (!ft_strcmp(command->name, "pwd"))
		g_minishell.last_return = bt_pwd();
	else if (!ft_strcmp(command->name, "unset"))
		g_minishell.last_return = bt_unset(&command->args[1]);
	else if (!ft_strcmp(command->name, "env"))
		g_minishell.last_return = bt_env();
	else if (!ft_strcmp(command->name, "export"))
		g_minishell.last_return = bt_export(&command->args[1]);
	else if (!ft_strcmp(command->name, "exit"))
		bt_exit(command->args);
	g_minishell.is_executing = 0;
	return (0);
}

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

int	bt_exit(char **args)
{
	int	ret_value;

	printf("exit\n");
	if (gc_strarray_size(args) > 2)
	{
		ft_dprintf(STDERR_FILENO, "minishell: exit: too many arguments\n");
		return (1);
	}
	if (args[1])
		ret_value = ft_atoi(args[1]);
	else
		ret_value = EXIT_SUCCESS;
	gc_clean(get_gc());
	exit(ret_value);
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
