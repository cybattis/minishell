#include "libft.h"
#include "parsing.h"

static t_err_or_charptr	get_next_chars(t_parser *parser, int expand_vars);

t_err_or_charptr	get_next_word(char *str, int expand_vars)
{
	t_err_or_charptr	result;
	t_parser			parser;
	char				*word;

	parser.i = 0;
	parser.str = skip_spaces(str);
	word = gc_strdup(get_gc(), "");
	while (parser.str[parser.i])
	{
		result = get_next_chars(&parser, expand_vars);
		if (result.error)
		{
			gc_free(get_gc(), word);
			return (result);
		}
		if (!result.result)
			break ;
		word = gc_strjoin(get_gc(), word, result.result, FREE_BOTH);
	}
	return ((t_err_or_charptr){NULL, word});
}

t_err_or_charptr	get_next_word_parser(t_parser *parser, int expand_vars)
{
	t_err_or_charptr	result;
	char				*word;

	word = gc_strdup(get_gc(), "");
	while (parser->str[parser->i])
	{
		result = get_next_chars(parser, expand_vars);
		if (result.error)
		{
			gc_free(get_gc(), word);
			return (result);
		}
		if (!result.result)
			break ;
		word = gc_strjoin(get_gc(), word, result.result, FREE_BOTH);
	}
	return ((t_err_or_charptr){NULL, word});
}

//TODO: handle spaces inside of env vars
static t_err_or_charptr	get_next_chars(t_parser *parser, int expand_vars)
{
	t_err_or_charptr	result;

	result.error = NULL;
	if (parser->str[parser->i] == '\'')
		result = get_single_quotes(parser);
	else if (parser->str[parser->i] == '"')
		result = get_double_quotes(parser);
	else if (expand_vars && parser->str[parser->i] == '$')
		result.result = get_env_var_raw(parser);
	else if (ft_isspace(parser->str[parser->i])
				|| is_operator_char(parser->str[parser->i]))
		result.result = NULL;
	else
	{
		result.result = gc_substr(get_gc(), parser->str, parser->i, 1);
		parser->i++;
	}
	return (result);
}
