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
		execute_command(command_batch);
		destroy_command_batch(command_batch);
	}
}
