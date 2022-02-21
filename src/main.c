/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:48:09 by cybattis          #+#    #+#             */
/*   Updated: 2022/02/21 20:27:04 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_app	g_minishell;

int	main(void)
{
	char			*line_read;
	t_command_batch	command_batch;

	init_signal();
	gc_init(&g_minishell.gc, gc_callback, NULL);
	g_minishell.local_env = gc_calloc(&g_minishell.gc, 2, sizeof(char *));
	g_minishell.local_env[0] = 0;
	while (FT_TRUE)
	{
		line_read = ft_get_line();
		command_batch = parse_input(line_read);
		execute_command(command_batch);
	}
	return (0);
}
