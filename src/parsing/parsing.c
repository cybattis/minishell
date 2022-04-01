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
	printf("before splitting commands foorprint %d\n", gc_getfootprint(get_gc()));
	if (!split_input_into_commands(input, &command_batch))
		return (command_batch);
	if (command_batch.count == 0)
		return (command_batch);
	printf("before creating redirs foorprint %d\n", gc_getfootprint(get_gc()));
	if (!get_redirections(input, &command_batch))
		return (command_batch);
	printf("before creating parsers foorprint %d\n", gc_getfootprint(get_gc()));
	parsers = strip_out_operators(input, &command_batch);
	gc_free(get_gc(), input);
	printf("before tokenize foorprint %d\n", gc_getfootprint(get_gc()));
	tokenize_all(&lexers, parsers, command_batch.count);
	//for (int i = 0; i < command_batch.count; i++)
	//{
	//	printf("lexer[%d]: \n", i);
	//	for (int j = 0; j < (int)lexers[i].count; j++)
	//		printf("tokens[%d]: [%s]\n", i, lexers[i].tokens[j].str);
	//}
	printf("after tokenize foorprint %d\n", gc_getfootprint(get_gc()));
	destroy_parsers(parsers, command_batch.count);
	printf("after destroy parsers foorprint %d\n", gc_getfootprint(get_gc()));
	populate_command_batch(&command_batch, lexers, command_batch.count);
	printf("after command batch creation foorprint %d\n", gc_getfootprint(get_gc()));
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
