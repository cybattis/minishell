#include "libft.h"
#include "parsing.h"

t_command_batch	parse_input(char *input)
{
	t_command_batch	command_batch;
	t_lexer			*lexers;
	t_parser		*parsers;

	ft_memset(&command_batch, 0, sizeof (t_command_batch));
	//TODO: Maybe check for unfinished quotes here ?
	if (!split_input_into_commands(input, &command_batch))
		return (command_batch);
	if (command_batch.count == 0)
		return (command_batch);
	if (!get_redirections(input, &command_batch))
		return (command_batch);
	parsers = strip_out_operators(input, &command_batch);
	tokenize_all(&lexers, parsers, command_batch.count);
	populate_command_batch(&command_batch, lexers, command_batch.count);
	return (command_batch);
}