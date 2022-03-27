/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:48:09 by njennes           #+#    #+#             */
/*   Updated: 2022/03/25 15:00:58 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *token_to_str(int token)
{
	switch (token)
	{
		case TOKEN_COMMAND:
			return ("COMMAND");
		case TOKEN_ARG:
			return ("ARG");
		case TOKEN_END:
			return ("END");
		case TOKEN_EMPTY:
			return ("EMPTY");
		default:
			return ("UNKNOWN");
	}
}

static void	print_command_batch(t_command_batch batch)
{
	t_command	*command;

	printf("Command Batch --------------\n");
	printf("*  Commands: %d\n", (int)batch.count);
	for (int i = 0; i < (int)batch.count; i++)
	{
		command = &batch.commands[i];
		printf("*  Command [%d] ---------\n", i);
		printf("*    Name: [%s]\n", command->name);
		printf("*    is_piping: %d, is_redirecting: %d, is_biltin: %d\n", command->is_piping, command->is_redirecting, command->is_builtin);
		printf("*    Args: ---\n");
		for (int j = 0; command->args[j]; j++)
			printf("*      Args[%d]: [%s]\n", j, command->args[j]);
		if (command->is_redirecting)
		{
			printf("*    Redirs: ---\n");
			for (int j = 0; command->redirections[j].type; j++)
				printf("*      Redirs[%d]: [%s] - [%s]\n", j, token_to_str(command->redirections[j].type), command->redirections[j].file);
		}
	}
	printf("----------------------------\n");
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
		init_signal();
		line_read = ft_get_line();
		command_batch = parse_input(line_read);
		print_command_batch(command_batch);
		execute_command(command_batch);
		destroy_command_batch(command_batch);
	}
	return (0);
}
