/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 12:55:27 by cybattis          #+#    #+#             */
/*   Updated: 2022/02/17 15:20:03 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_signal(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SIG_BLOCK;
	sa.sa_handler = sig_handler;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGTSTP, SIG_IGN);
	return (0);
}

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
}
