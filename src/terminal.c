/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 16:48:07 by cybattis          #+#    #+#             */
/*   Updated: 2022/03/04 17:43:06 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <termios.h>

// TODO: put this in signal SIGINT
void disableRawMode(struct termios og_termios)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &og_termios);
}
void enableRawMode(struct termios og_termios)
{
	struct termios raw = og_termios;

	tcgetattr(STDIN_FILENO, &og_termios);
	raw.c_lflag &= ~(ECHO | ICANON | ISIG);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
