/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 16:48:07 by cybattis          #+#    #+#             */
/*   Updated: 2022/03/03 16:49:52 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <termios.h>

struct termios og_termios;

void disableRawMode()
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &og_termios);
}
void enableRawMode()
{
	struct termios raw = og_termios;

	tcgetattr(STDIN_FILENO, &og_termios);
	raw.c_lflag &= ~(ECHO);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
