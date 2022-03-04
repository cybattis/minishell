/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_batch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:46:20 by njennes           #+#    #+#             */
/*   Updated: 2022/03/04 14:13:31 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include "minishell.h"

int	is_redir_token(int token)
{
	if (token == TOKEN_REDIR_OUT || token == TOKEN_REDIR_OUT_APPEND ||
		token == TOKEN_REDIR_IN || token == TOKEN_REDIR_IN_APPEND ||
		token == TOKEN_PIPE)
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
	while (tokens[i].type == TOKEN_COMMAND || tokens[i].type == TOKEN_ARG)
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
//	printf("%zu\n", arg_count);
	args = gc_calloc(get_gc(), arg_count + 1, sizeof (char *));
	i = 0;
	j = 0;
	while (tokens[i].type == TOKEN_COMMAND || tokens[i].type == TOKEN_ARG)
	{
		if (tokens[i].type == TOKEN_COMMAND || tokens[i].type == TOKEN_ARG)
		{
			args[j] = gc_strdup(get_gc(), tokens[i].str);
//			printf("args %s\n", args[j]);
			j++;
		}
		i++;
	}
	return (args);
}

size_t	get_redirs_count(t_token *tokens)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	while (tokens[i].type == TOKEN_COMMAND || tokens[i].type == TOKEN_ARG ||
		   is_redir_token(tokens[i].type))
	{
		if (is_redir_token(tokens[i].type))
			count++;
		i++;
	}
	return (count);
}

t_redir	*get_redirections(t_token *tokens)
{
	t_redir	*redirs;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	redirs = gc_calloc(get_gc(), get_redirs_count(tokens) + 1, sizeof (t_redir));
	while (tokens[i].type == TOKEN_COMMAND || tokens[i].type == TOKEN_ARG ||
		   is_redir_token(tokens[i].type))
	{
		if (is_redir_token(tokens[i].type))
		{
			redirs[j].type = tokens[i].type;
			if ((tokens[i].type == TOKEN_REDIR_OUT ||
				tokens[i].type == TOKEN_REDIR_OUT_APPEND) &&
				tokens[i + 1].type == TOKEN_FILE)
			{
				redirs[j].file = gc_strdup(get_gc(), tokens[i + 1].str);
			}
			j++;
		}
		i++;
	}
	return (redirs);
}

static void	populate_commands(t_lexer lexer, t_command *commands)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (lexer.tokens[i].type != TOKEN_END)
	{
		commands[j].args = get_command_args(&lexer.tokens[i]);
		commands[j].redirections = get_redirections(&lexer.tokens[i]);
		if (commands[j].redirections[0].type)
			commands[j].is_redirecting = 1;
		while (lexer.tokens[i].type != TOKEN_COMMAND)
			i++;
		commands[j].name = gc_strdup(get_gc(), lexer.tokens[i].str);
		commands[j].is_builtin = is_builtin_command(commands[j].name);
		while (lexer.tokens[i].type != TOKEN_END &&
				lexer.tokens[i].type != TOKEN_PIPE)
			i++;
		if (lexer.tokens[i].type == TOKEN_PIPE)
		{
			commands[j].is_piping = FT_TRUE;
			i++;
		}
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
