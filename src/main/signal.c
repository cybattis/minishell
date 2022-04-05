/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 12:55:27 by cybattis          #+#    #+#             */
/*   Updated: 2022/04/05 20:32:33 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "readline.h"
#include "core.h"
#include <signal.h>

int	init_signal(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGPIPE, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	return (0);
}

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		if (g_minishell.is_heredoc)
		{
			g_minishell.is_heredoc = 0;
			close(STDIN_FILENO);
			g_minishell.last_return = 130;
			return ;
		}
		rl_on_new_line();
		rl_replace_line("", 0);
		if (!g_minishell.is_executing)
			rl_redisplay();
		if (!g_minishell.has_child)
			g_minishell.last_return = 1;
	}
	if (signum == SIGQUIT)
		printf("Quit: 3\n");
	if (signum == SIGPIPE)
	{
		gc_clean(get_gc());
		exit(141);
	}
}
