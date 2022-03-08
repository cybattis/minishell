/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 12:55:27 by cybattis          #+#    #+#             */
/*   Updated: 2022/03/07 17:04:18 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include "minishell.h"
#include "readline.h"
#include <signal.h>

int	init_signal(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = sig_handler;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

// TODO: make ^C invisible
// TODO: impl. signal for child -- in cat ˆD does nothing and is visible
// TODO: cat | cat | ls -- enter quit one cat 
