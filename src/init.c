/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:46:20 by njennes           #+#    #+#             */
/*   Updated: 2022/03/05 16:13:47 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/minishell.h"
#include <sys/param.h>
#include <unistd.h>

extern char	**environ;

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

	old_shlvl = getenv("SHLVL");
	if (!old_shlvl)
		environ = gc_strarray_append(get_gc(), environ, "SHLVL=0");
	old_shlvl = getenv("SHLVL");
	old_shell_level = ft_atoi(old_shlvl);
	new_shell_level = gc_itoa(get_gc(), old_shell_level + 1);
	set_env_var("SHLVL", new_shell_level);
	gc_free(get_gc(), new_shell_level);
}

void	update_shell_env_vars(void)
{
	environ = gc_strarray_from(get_gc(), environ, gc_strarray_size(environ));
	update_shell_path();
	update_shell_level();
}

void	init_minishell(char **envp)
{
	init_signal();
	gc_init(&g_minishell.gc, gc_callback, NULL);
	g_minishell.last_return = 0;
	g_minishell.base_env = envp;
	tcgetattr(STDIN_FILENO, &g_minishell.og_termios);
	update_shell_env_vars();
}
