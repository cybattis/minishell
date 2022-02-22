/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:46:20 by njennes           #+#    #+#             */
/*   Updated: 2022/02/16 22:17:25 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/minishell.h"
#include <sys/param.h>
#include <unistd.h>

extern char	**environ;

void	update_shell_path()
{
	char	*path_to_minishell;
	char	buf[MAXPATHLEN];

	getcwd(buf, MAXPATHLEN);
	path_to_minishell = gc_strjoin(get_gc(), buf, "/minishell", 0);
	set_env_var("SHELL", path_to_minishell);
	gc_free(get_gc(), path_to_minishell);
}

void	update_shell_level()
{
	char	*new_shell_level;
	int		old_shell_level;

	old_shell_level = ft_atoi(getenv("SHLVL"));
	new_shell_level = gc_itoa(get_gc(), old_shell_level + 1);
	set_env_var("SHLVL", new_shell_level);
	gc_free(get_gc(), new_shell_level);
}

void	update_shell_env_vars()
{
	environ = gc_strarray_from(get_gc(), environ, gc_strarray_size(environ));
	update_shell_path();
	update_shell_level();
}

void	init_minishell(char **envp)
{
	init_signal();
	gc_init(&g_minishell.gc, gc_callback, NULL);
	g_minishell.local_env = gc_calloc(&g_minishell.gc, 2, sizeof(char *));
	g_minishell.local_env[0] = 0;
	g_minishell.base_env = envp;
	update_shell_env_vars();
}
