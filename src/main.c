/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:48:09 by cybattis          #+#    #+#             */
/*   Updated: 2022/02/19 16:43:04 by cybattis         ###   ########.fr       */
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
		execute_cmd(command_batch);
	}
	return (0);
}
