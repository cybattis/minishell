/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_batch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 13:35:55 by njennes           #+#    #+#             */
/*   Updated: 2022/03/27 13:35:56 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include "core.h"

static void		populate_command(t_command *command, t_lexer lexer);
static char		**get_args(t_lexer lexer);
static char		*get_command_name(t_command *command, t_lexer *lexer);
static void		decimate_lexers(t_lexer *lexers, size_t count);

int				is_builtin(char *command);
size_t			get_arg_count(t_lexer *lexer);

void	populate_command_batch(t_command_batch *batch,
		t_lexer *lexers, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		populate_command(&batch->commands[i], lexers[i]);
		i++;
	}
	decimate_lexers(lexers, count);
}

static void	populate_command(t_command *command, t_lexer lexer)
{
	command->name = get_command_name(command, &lexer);
	command->is_builtin = is_builtin(command->name);
	command->args = get_args(lexer);
}

static char	**get_args(t_lexer lexer)
{
	char	**args;
	size_t	count;
	size_t	i;
	size_t	j;

	count = get_arg_count(&lexer);
	args = gc_calloc(get_gc(), count + 1, sizeof (char **));
	i = 0;
	j = 0;
	while (i < lexer.count)
	{
		if (lexer.tokens[i].type == TOKEN_ARG
			|| lexer.tokens[i].type == TOKEN_COMMAND)
		{
			args[j] = lexer.tokens[i].str;
			j++;
		}
		i++;
	}
	return (args);
}

static char	*get_command_name(t_command *command, t_lexer *lexer)
{
	size_t	i;

	i = 0;
	while (command->redirections[i].type)
	{
		if (!command->redirections[i].file)
			return (NULL);
		i++;
	}
	i = 0;
	while (i < lexer->count)
	{
		if (lexer->tokens[i].type == TOKEN_COMMAND)
			return (lexer->tokens[i].str);
		i++;
	}
	return (NULL);
}

static void		decimate_lexers(t_lexer *lexers, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		gc_free(get_gc(), lexers[i].tokens);
		i++;
	}
	gc_free(get_gc(), lexers);
}
