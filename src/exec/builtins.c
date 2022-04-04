/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 15:04:11 by cybattis          #+#    #+#             */
/*   Updated: 2022/04/04 16:11:02 by njennes          ###   ########.fr       */
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
	size_t	i;
	size_t	j;
	int		new_line;

	i = 1;
	new_line = 1;
	while (cmd->args[i] && cmd->args[i][0] == '-')
	{
		j = 1;
		while (cmd->args[i][j] == 'n')
			j++;
		if (cmd->args[i][j])
			break ;
		i++;
		new_line = 0;
	}
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[++i])
			printf(" ");
	}
	if (new_line)
		printf("\n");
	return (0);
}

int	bt_exit(char **args)
{
	int	ret_value;

	ft_dprintf(STDERR_FILENO, "exit\n");
	if (args[1] && !ft_strisdigit(args[1]))
	{
		ft_dprintf(STDERR_FILENO,
			"minishell: exit: %s: numeric argument required\n", args[1]);
		gc_clean(get_gc());
		exit(255);
	}
	if (gc_strarray_size(args) > 2)
	{
		ft_dprintf(STDERR_FILENO, "minishell: exit: too many arguments\n");
		return (1);
	}
	if (args[1])
		ret_value = ft_atoi(args[1]);
	else
		ret_value = g_minishell.last_return;
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

	if (!path || strcmp(path, "~") == 0)
		path = get_env("HOME");
	if (!path)
	{
		ft_dprintf(STDERR_FILENO, "minishell: cd: HOME not set\n");
		return (1);
	}
	if (chdir(path))
	{
		ft_dprintf(STDERR_FILENO, "minishell: cd: %s: %s\n", path,
			strerror(errno));
		return (1);
	}
	set_env_var("OLDPWD", getenv("PWD"));
	set_env_var("PWD", getcwd(buf, MAXPATHLEN));
	return (0);
}
