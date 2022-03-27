/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 13:35:57 by njennes           #+#    #+#             */
/*   Updated: 2022/03/27 13:35:58 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include "core.h"

static int	get_pipe_count(char *str);
static int	ends_with_pipe(char *str);
static int	contains_char(char *str);
static void	setup_piping_commands(t_command_batch *batch);

int			skip_quotes_command_split(char *str,
				size_t *i, int *encountered_char);
int			last_char_is_pipe(char *str, size_t *i);
int			is_legal_pipe(int *encountered_char, int *count);

int	split_input_into_commands(char *input, t_command_batch *batch)
{
	int	pipe_count;

	if (ends_with_pipe(input))
		return (error_return(
				"minishell: syntax error near unexpected token '|'", 0));
	pipe_count = get_pipe_count(input);
	if (pipe_count < 0)
		return (0);
	batch->count = pipe_count;
	if (contains_char(input))
		batch->count++;
	batch->commands = gc_calloc(get_gc(),
			batch->count + 1, sizeof (t_command));
	if (batch->count)
		setup_piping_commands(batch);
	return (1);
}

static int	get_pipe_count(char *str)
{
	size_t	i;
	int		count;
	int		encountered_char;

	i = 0;
	count = 0;
	encountered_char = 0;
	while (str[i])
	{
		if (skip_quotes_command_split(str, &i, &encountered_char))
			continue ;
		else if (str[i] == '|')
		{
			if (last_char_is_pipe(str, &i))
				continue ;
			if (!is_legal_pipe(&encountered_char, &count))
				return (error_return(
						"minishell: syntax error near unexpected token '|'",
						-1));
		}
		else if (ft_isprint(str[i]) && !ft_isspace(str[i]))
			encountered_char = 1;
		i++;
	}
	return (count);
}

static int	contains_char(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (ft_isprint(str[i]) && !ft_isspace(str[i]))
			return (1);
		i++;
	}
	return (0);
}

static int	ends_with_pipe(char *str)
{
	char	*last_pipe;

	last_pipe = ft_strrchr(str, '|');
	if (last_pipe)
		last_pipe++;
	else
		return (0);
	while (*last_pipe)
	{
		if (ft_isprint(*last_pipe) && !ft_isspace(*last_pipe))
			return (0);
		last_pipe++;
	}
	return (1);
}

static void	setup_piping_commands(t_command_batch *batch)
{
	size_t	i;

	i = 0;
	while (i < batch->count - 1)
	{
		batch->commands[i].is_piping = 1;
		i++;
	}
}
