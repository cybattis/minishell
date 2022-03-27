/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_batch_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 13:35:53 by njennes           #+#    #+#             */
/*   Updated: 2022/03/27 13:35:54 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"

 size_t get_arg_count(t_lexer *lexer)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	while (i < lexer->count)
	{
		if (lexer->tokens[i].type == TOKEN_ARG
			|| lexer->tokens[i].type == TOKEN_COMMAND)
			count++;
		i++;
	}
	return (count);
}

int	is_builtin(char *command)
{
	if (ft_strcmp(command, "echo") == 0)
		return (1);
	if (ft_strcmp(command, "exit") == 0)
		return (1);
	if (ft_strcmp(command, "export") == 0)
		return (1);
	if (ft_strcmp(command, "cd") == 0)
		return (1);
	if (ft_strcmp(command, "pwd") == 0)
		return (1);
	if (ft_strcmp(command, "unset") == 0)
		return (1);
	return (0);
}
