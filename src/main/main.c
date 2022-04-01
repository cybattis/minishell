/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:48:09 by cybattis          #+#    #+#             */
/*   Updated: 2022/03/27 14:23:15 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "core.h"

int	main(int argc, char **argv, char **envp)
{
	char			*line_read;
	t_command_batch	command_batch;

	init_minishell(argc, argv, envp);
	line_read = argv[1];
	while (line_read)
	{
		printf("footprint: %d\n", gc_getfootprint(get_gc()));
		//init_signal();
		//line_read = ft_get_line();
		command_batch = parse_input(line_read);
		//execute_command(command_batch);
		destroy_command_batch(command_batch);
		printf("footprint: %d\n", gc_getfootprint(get_gc()));
		getchar();
	}
	return (0);
}
