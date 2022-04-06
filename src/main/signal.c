/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 12:55:27 by cybattis          #+#    #+#             */
/*   Updated: 2022/04/06 14:26:59 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "readline.h"
#include "core.h"
#include <signal.h>

static void	sigint_handler(void);

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
		sigint_handler();
	if (signum == SIGQUIT)
		ft_dprintf(STDERR_FILENO, "Quit: 3\n");
	if (signum == SIGPIPE)
	{
		gc_clean(get_gc());
		exit(141);
	}
}

static void	sigint_handler(void)
{
	if (g_minishell.is_heredoc)
	{
		if (g_minishell.is_piping == 0)
			ft_dprintf(STDERR_FILENO, "\n");
		g_minishell.is_heredoc = SIGINT_HD;
		close(STDIN_FILENO);
		g_minishell.last_return = 130;
		return ;
	}
	ft_dprintf(STDERR_FILENO, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	if (!g_minishell.is_executing)
		rl_redisplay();
	if (!g_minishell.has_child)
		g_minishell.last_return = 1;
}
