/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:48:09 by cybattis          #+#    #+#             */
/*   Updated: 2022/02/19 15:15:45 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char			*line_read;
	t_command_batch	command_batch;

	init_signal();
	while (FT_TRUE)
	{
		line_read = ft_get_line();
		command_batch = parse_input(line_read);
		printf("%s\n", command_batch.commands[0].name);
		// execute_cmd();
	}
	return (0);
}
