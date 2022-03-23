#include "libft.h"
#include "parsing.h"

static void	check_for_error(t_parser *parser, t_err_or_charptr *result);

t_err_or_charptr	get_double_quotes(t_parser *parser)
{
	t_err_or_charptr	result;

	parser->i++;
	result.result = gc_strdup(get_gc(), "");
	result.error = NULL;
	while (parser->str[parser->i] && parser->str[parser->i] != '"')
	{
		if (parser->str[parser->i] == '$')
			result.result = gc_strjoin(get_gc(), result.result, get_env_var_raw(parser), FREE_BOTH);
		else
			result.result = gc_strappend(get_gc(), result.result, parser->str[parser->i++]);
	}
	check_for_error(parser, &result);
	return (result);
}

static void	check_for_error(t_parser *parser, t_err_or_charptr *result)
{
	if (parser->str[parser->i])
		parser->i++;
	else
	{
		result->error = gc_strdup(get_gc(), "minishell: syntax error: expected `\"\' but got `newline\'");
		gc_destroy(get_gc(), (void **)&result->result);
	}
}
