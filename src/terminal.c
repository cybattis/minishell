/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 16:48:07 by cybattis          #+#    #+#             */
/*   Updated: 2022/03/24 17:14:44 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "core.h"
#include <unistd.h>
#include <termios.h>

void	enable_alt_termmode(void)
{
	struct termios	new;

	if (!isatty(STDIN_FILENO)) {
		perror("Input is not a TTY");
		return ;
	}
	tcgetattr(STDIN_FILENO, &g_minishell.old);
	g_minishell.old = new;
	new.c_iflag |= ~ISIG;
	new.c_lflag |= ~ECHO;
	new.c_cc[VINTR] = 1;
	new.c_cc[VMIN] = 0;
	new.c_cc[VTIME] = 1;
	tcsetattr(STDIN_FILENO, TCSANOW, &new);
}

void	disable_alt_termmode(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &g_minishell.old);
}
