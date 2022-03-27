/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 13:36:22 by njennes           #+#    #+#             */
/*   Updated: 2022/03/27 13:36:23 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "core.h"

static void	destroy_parsers(t_parser *parsers, size_t count);

t_command_batch	parse_input(char *input)
{
	t_command_batch	command_batch;
	t_lexer			*lexers;
	t_parser		*parsers;

	ft_memset(&command_batch, 0, sizeof (t_command_batch));
	if (contains_unfinished_quotes(input))
		input = ask_for_quote(input);
	if (!split_input_into_commands(input, &command_batch))
		return (command_batch);
	if (command_batch.count == 0)
		return (command_batch);
	if (!get_redirections(input, &command_batch))
		return (command_batch);
	parsers = strip_out_operators(input, &command_batch);
	gc_free(get_gc(), input);
	tokenize_all(&lexers, parsers, command_batch.count);
	destroy_parsers(parsers, command_batch.count);
	populate_command_batch(&command_batch, lexers, command_batch.count);
	return (command_batch);
}

static void	destroy_parsers(t_parser *parsers, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		gc_free(get_gc(), parsers[i].str);
		i++;
	}
	gc_free(get_gc(), parsers);
}
