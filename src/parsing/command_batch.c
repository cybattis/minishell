/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_batch.c                                    :+:      :+:    :+:   */
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

static void		populate_commands(t_lexer lexer, t_command *commands);
static size_t	get_command_count(t_lexer lexer);
static char		**get_command_args(t_token *tokens);
static t_redir	*get_redirections(t_token *tokens);

void	create_command_batch(t_lexer lexer, t_command_batch *batch)
{
	size_t	command_count;

	command_count = get_command_count(lexer);
	batch->count = command_count;
	batch->commands = gc_calloc(get_gc(), command_count + 1, sizeof(t_command));
	populate_commands(lexer, batch->commands);
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
		while (lexer.tokens[i].type && lexer.tokens[i].type != TOKEN_COMMAND)
			i++;
		commands[j].name = gc_strdup(get_gc(), lexer.tokens[i].str);
		commands[j].is_builtin = is_builtin_command(commands[j].name);
		while (lexer.tokens[i].type && lexer.tokens[i].type != TOKEN_PIPE)
			i++;
		if (lexer.tokens[i].type == TOKEN_PIPE)
		{
			commands[j].is_piping = FT_TRUE;
			i++;
		}
		j++;
	}
}

static size_t	get_command_count(t_lexer lexer)
{
	size_t	i;
	size_t	count;

	if (lexer.tokens[0].type == TOKEN_END)
		return (0);
	i = 0;
	count = 1;
	while (i < lexer.count)
	{
		if (lexer.tokens[i].type == TOKEN_PIPE)
			count++;
		i++;
	}
	return (count);
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
	while (tokens[i].type == TOKEN_COMMAND || tokens[i].type == TOKEN_ARG
		|| tokens[i].type == TOKEN_FILE || is_redir_token(tokens[i].type))
	{
		if (tokens[i].type == TOKEN_COMMAND || tokens[i].type == TOKEN_ARG)
		{
			args[j] = gc_strdup(get_gc(), tokens[i].str);
			j++;
		}
		i++;
	}
	return (args);
}

static t_redir	*get_redirections(t_token *tokens)
{
	t_redir	*redirs;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	redirs = gc_calloc(get_gc(), get_redirs_count(tokens) + 1, sizeof(t_redir));
	while (tokens[i].type == TOKEN_COMMAND || tokens[i].type == TOKEN_ARG
		|| is_redir_token(tokens[i].type) || tokens[i].type == TOKEN_FILE)
	{
		if (is_redir_token(tokens[i].type))
		{
			redirs[j].type = tokens[i].type;
			redirs[j].file = gc_strdup(get_gc(), tokens[i + 1].str);
			j++;
		}
		i++;
	}
	return (redirs);
}
