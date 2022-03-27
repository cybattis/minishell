/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 14:23:04 by njennes           #+#    #+#             */
/*   Updated: 2022/03/27 14:23:04 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "core.h"

int	wait_for_child(pid_t pid)
{
	int	wstatus;

	g_minishell.has_child = 0;
	waitpid(pid, &wstatus, 0);
	get_child_return(wstatus);
	g_minishell.is_executing = 0;
	return (0);
}

void	get_child_return(int wstatus)
{
	int	sig;

	if (WIFEXITED(wstatus))
		g_minishell.last_return = WEXITSTATUS(wstatus);
	else
	{
		sig = WTERMSIG(wstatus);
		if (sig == SIGINT)
			g_minishell.last_return = 130;
		else if (sig == SIGQUIT)
			g_minishell.last_return = 131;
	}
}
