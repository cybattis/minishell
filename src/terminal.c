/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 16:48:07 by cybattis          #+#    #+#             */
/*   Updated: 2022/03/09 10:11:40 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <termios.h>

void	enable_alt_termmode(void)
{
	struct termios	raw;

	tcgetattr(STDOUT_FILENO, &raw);
	g_minishell.termios = raw;
	raw.c_cflag = ~ISIG;
	tcsetattr(STDOUT_FILENO, TCSANOW, &raw);
}

void	disable_alt_termmode(void)
{
	tcsetattr(STDOUT_FILENO, TCSANOW, &g_minishell.termios);
}
