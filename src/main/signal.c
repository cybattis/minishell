/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 12:55:27 by cybattis          #+#    #+#             */
/*   Updated: 2022/03/23 16:50:39 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (!g_minishell.is_executing)
			rl_redisplay();
	}
}

//int	init_signal_child(void)
//{
//	struct sigaction	sa;
//
//	sigemptyset(&sa.sa_mask);
//	sa.sa_flags = 0;
//	sa.sa_handler = sig_handler_child;
//	sigaction(SIGINT, &sa, NULL);
//	signal(SIGTSTP, SIG_IGN);
//	signal(SIGQUIT, SIG_IGN);
//	return (0);
//}

void	sig_handler_child(int signum)
{
	if (signum == SIGINT)
	{
		exit(130);
	}
}

// TODO: make ^C invisible
// 		SIGINT child return = 130
// TODO: cat | cat | ls -- enter quit one cat
// TODO: make relative command ex: LS ou CAT working -- tolower()
// TODO: symbolic link
// TODO: add error check and retrun for builtins
