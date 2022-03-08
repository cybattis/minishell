/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_batch_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <cybattis@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:46:20 by njennes           #+#    #+#             */
/*   Updated: 2022/03/05 16:01:38 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include "minishell.h"

size_t	get_arg_count(t_token *tokens)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (tokens[i].type == TOKEN_COMMAND || tokens[i].type == TOKEN_ARG
		|| tokens[i].type == TOKEN_FILE || is_redir_token(tokens[i].type))
	{
		if (tokens[i].type == TOKEN_COMMAND || tokens[i].type == TOKEN_ARG)
			count++;
		i++;
	}
	return (count);
}

int	is_builtin_command(char *str)
{
	if (!str)
		return (1);
	if (ft_strcmp(str, "echo") == 0)
		return (1);
	if (ft_strcmp(str, "pwd") == 0)
		return (1);
	if (ft_strcmp(str, "exit") == 0)
		return (1);
	if (ft_strcmp(str, "cd") == 0)
		return (1);
	if (ft_strcmp(str, "export") == 0)
		return (1);
	if (ft_strcmp(str, "unset") == 0)
		return (1);
	if (ft_strcmp(str, "env") == 0)
		return (1);
	return (0);
}

size_t	get_redirs_count(t_token *tokens)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	while (tokens[i].type == TOKEN_COMMAND || tokens[i].type == TOKEN_ARG
		|| is_redir_token(tokens[i].type) || tokens[i].type == TOKEN_FILE)
	{
		if (is_redir_token(tokens[i].type))
			count++;
		i++;
	}
	return (count);
}
