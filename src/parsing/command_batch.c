/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_batch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:46:20 by njennes           #+#    #+#             */
/*   Updated: 2022/02/19 15:46:51 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include "minishell.h"

int	is_redir_token(int token)
{
	if (token == TOKEN_REDIR_OUT || token == TOKEN_REDIR_OUT_APPEND ||
		token == TOKEN_REDIR_IN || token == TOKEN_REDIR_IN_APPEND)
		return (1);
	return (0);
}

static size_t	get_command_count(t_lexer lexer)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (i < lexer.count)
	{
		if (lexer.tokens[i].type == TOKEN_COMMAND)
			count++;
		i++;
	}
	return (count);
}

static size_t	get_arg_count(t_token *tokens)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (tokens[i].type == TOKEN_COMMAND || tokens[i].type == TOKEN_ARG ||
			is_redir_token(tokens[i].type))
	{
		if (tokens[i].type == TOKEN_COMMAND || tokens[i].type == TOKEN_ARG)
			count++;
		i++;
	}
	return (count);
}

static int	is_builtin_command(char *str)
{
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

static char	**get_command_args(t_token *tokens)
{
	size_t	i;
	size_t	j;
	size_t	arg_count;
	char	**args;

	arg_count = get_arg_count(tokens);
	args = gc_calloc(get_gc(), arg_count + 1, sizeof (char *));
	i = 0;
	j = 0;
	while (tokens[i].type == TOKEN_COMMAND || tokens[i].type == TOKEN_ARG ||
			is_redir_token(tokens[i].type))
	{
		if (tokens[i].type == TOKEN_COMMAND || tokens[i].type == TOKEN_ARG)
		{
			args[j] = gc_strdup(get_gc(),tokens[i].str);
			j++;
		}
		i++;
	}
	return (args);
}

static int	get_redirection_type(t_token *tokens)
{
	size_t	i;

	i = 0;
	while (tokens[i].type && !is_redir_token(tokens[i].type) &&
			tokens[i].type != TOKEN_PIPE)
		i++;
	if (is_redir_token(tokens[i].type))
		return (tokens[i].type);
	return (TOKEN_END);
}

static char	*get_redirection_file(t_token *tokens)
{
	size_t	i;
	char	*file_name;

	i = 0;
	while (tokens[i].type && !is_redir_token(tokens[i].type))
		i++;
	i++;
	file_name = gc_strdup(get_gc(),tokens[i].str);
	return (file_name);
}

static size_t	get_command_length(t_token *tokens)
{
	size_t	i;

	i = 0;
	while (tokens[i].type && tokens[i].type != TOKEN_COMMAND)
		i++;
	return (i);
}

static void	populate_commands(t_lexer lexer, t_command *commands)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (lexer.tokens[i].type != TOKEN_END)
	{
		commands[j].name = gc_strdup(get_gc(), lexer.tokens[i].str);
		commands[j].is_builtin = is_builtin_command(commands[j].name);
		commands[j].args = get_command_args(&lexer.tokens[i]);
		i++;
		commands[j].redirection_type = get_redirection_type(&lexer.tokens[i]); //TODO: Check for multiple redirs
		if (commands[j].redirection_type)
		{
			commands[j].is_redirecting = 1;
			commands[j].redirection_file = get_redirection_file(&lexer.tokens[i]);
		}
		i += get_command_length(&lexer.tokens[i]);
		j++;
	}
}

void	create_command_batch(t_lexer lexer, t_command_batch *batch)
{
	size_t	command_count;

	command_count = get_command_count(lexer);
	batch->count = command_count;
	batch->commands = gc_calloc(get_gc(), command_count, sizeof (t_command));
	populate_commands(lexer, batch->commands);
}
