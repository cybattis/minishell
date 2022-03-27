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

void	lexer_print(t_lexer lexer)
{
	printf("lexer size: [%zu]\n", lexer.count);
	for (int i = 0; i < (int)lexer.count; i++)
		printf("lexer[%d]: [%s] [%s]\n", i, token_to_str(lexer.tokens[i].type), lexer.tokens[i].str);
}

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
	for (int i = 0; i < command_batch.count; i++)
		printf("parser[%d]: [%s]\n", i, parsers[i].str);
	gc_free(get_gc(), input);
	tokenize_all(&lexers, parsers, command_batch.count);
	for (int i = 0; i < command_batch.count; i++)
		lexer_print(lexers[i]);
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
