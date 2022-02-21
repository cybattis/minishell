/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:48:09 by cybattis          #+#    #+#             */
/*   Updated: 2022/02/21 18:48:53 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "readline.h"

t_gc	g_gc;

int	main(void)
{
	char			*line_read;
	t_command_batch	command_batch;

	init_signal();
	gc_init(&g_gc, gc_callback, NULL);
	while (FT_TRUE)
	{
		line_read = ft_get_line();
		command_batch = parse_input(line_read);
		execute_command(command_batch);
	}
	return (0);
}
