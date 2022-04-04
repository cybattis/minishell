/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:48:09 by cybattis          #+#    #+#             */
/*   Updated: 2022/04/01 15:04:36 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char			*line_read;
	t_command_batch	command_batch;

	handle_minishell_arg(argc, argv);
	init_minishell(argc, argv, envp);
	while (FT_TRUE)
	{
		init_signal();
		line_read = ft_get_line();
		command_batch = parse_input(line_read);
		execute_command(command_batch);
		destroy_command_batch(command_batch);
	}
	return (0);
}
