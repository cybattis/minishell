/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:48:09 by cybattis          #+#    #+#             */
/*   Updated: 2022/03/24 16:41:43 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_command_batch(t_command_batch batch)
{
}

int	main(int argc, char **argv, char **envp)
{
	char			*line_read;
	t_command_batch	command_batch;

	(void)argc;
	(void)argv;
	init_minishell(envp);
	while (FT_TRUE)
	{
		line_read = ft_get_line();
		command_batch = parse_input(line_read);
		print_command_batch(command_batch);
		execute_command(command_batch);
		destroy_command_batch(command_batch);
	}
}
