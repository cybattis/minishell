#include "libft.h"
#include "parsing.h"

static void	check_for_error(t_parser *parser, t_err_or_charptr *result);

t_err_or_charptr	get_single_quotes(t_parser *parser)
{
	t_err_or_charptr	result;
	size_t				start;

	parser->i++;
	start = parser->i;
	result.error = NULL;
	while (parser->str[parser->i] && parser->str[parser->i] != '\'')
		parser->i++;
	result.result = gc_substr(get_gc(), parser->str, start, parser->i - start);
	check_for_error(parser, &result);
	return (result);
}

static void	check_for_error(t_parser *parser, t_err_or_charptr *result)
{
	if (parser->str[parser->i])
		parser->i++;
	else
	{
		result->error = gc_strdup(get_gc(), "minishell: syntax error: expected `\'\' but got `newline\'");
		gc_destroy(get_gc(), &result->result);
	}
}
