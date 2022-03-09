/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:46:20 by njennes           #+#    #+#             */
/*   Updated: 2022/03/05 16:02:04 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include "minishell.h"

void	lexer_print(t_lexer *lexer)
{
	size_t	size;
	size_t	i;

	size = lexer->count;
	i = 0;
	while (i < size)
	{
		printf("lexer[%d]: %s:%d\n", (int)i, lexer->tokens[i].str, lexer->tokens[i].type);
		i++;
	}
}

t_command_batch	parse_input(char *input)
{
	t_command_batch	command_batch;
	t_lexer			lexer;

	lexer = tokenize_input(input);
	ft_memset(&command_batch, 0, sizeof (t_command_batch));
	if (!check_parsing_errors(lexer))
		return (command_batch);
	create_command_batch(lexer, &command_batch);
	lexer_print(&lexer);
	lexer_destroy(&lexer);
	return (command_batch);
}
