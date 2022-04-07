/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:46:20 by njennes           #+#    #+#             */
/*   Updated: 2022/04/07 12:58:11 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "core.h"
#include <sys/param.h>
#include <unistd.h>
#include <fcntl.h>

t_mini		g_minishell;

void	update_shell_path(void)
{
	char	*path_to_minishell;
	char	buf[MAXPATHLEN];

	getcwd(buf, MAXPATHLEN);
	path_to_minishell = gc_strjoin(get_gc(), buf, "/minishell", 0);
	set_env_var("SHELL", path_to_minishell);
	gc_free(get_gc(), path_to_minishell);
}

void	update_shell_level(void)
{
	char	*new_shell_level;
	char	*old_shlvl;
	int		old_shell_level;

	old_shlvl = get_env("SHLVL");
	if (!old_shlvl)
		g_minishell.env = gc_strarray_append(get_gc(),
				g_minishell.env, "SHLVL=0");
	old_shlvl = get_env("SHLVL");
	old_shell_level = ft_atoi(old_shlvl);
	new_shell_level = gc_itoa(get_gc(), old_shell_level + 1);
	set_env_var("SHLVL", new_shell_level);
	gc_free(get_gc(), new_shell_level);
}

void	update_shell_env_vars(char **envp)
{
	g_minishell.env = gc_strarray_from(get_gc(), envp, gc_strarray_size(envp));
	update_shell_path();
	update_shell_level();
}

int	init_inputrc(void)
{
	char	*path;
	char	*inputrc;
	int		fd;

	path = gc_strjoin(get_gc(), get_env("HOME"), "/.inputrc", FREE_NONE);
	if (!access(path, F_OK))
		return (0);
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
	{
		gc_free(get_gc(), path);
		return (ft_print_errno());
	}
	inputrc = "set colored-stats on\nset echo-control-characters off\n";
	write(fd, inputrc, ft_strlen(inputrc));
	gc_free(get_gc(), path);
	close(fd);
	return (0);
}

void	init_minishell(int argc, char **argv, char **envp)
{
	gc_init(&g_minishell.gc, gc_callback, NULL);
	g_minishell.last_return = 0;
	g_minishell.is_executing = 0;
	g_minishell.has_child = 0;
	g_minishell.is_heredoc = 0;
	g_minishell.argv = argv;
	g_minishell.argc = argc;
	update_shell_env_vars(envp);
	init_inputrc();
}
