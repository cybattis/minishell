#include "libft.h"
#include "parsing.h"

static char *handle_question_mark(t_parser *parser);

char	*get_env_var_name(t_parser *parser)
{
	char	*name;

	parser->i++;
	if (!is_envchar(parser->str[parser->i]))
		return handle_question_mark(parser);
	name = gc_strdup(get_gc(), "");
	if (ft_isdigit(parser->str[parser->i]))
		return (name);
	while (is_envchar(parser->str[parser->i]))
	{
		name = gc_strappend(get_gc(), name, parser->str[parser->i]);
		parser->i++;
	}
	return (name);
}

int	is_envchar(char c)
{
	if (ft_isalpha(c) || c == '_')
		return (1);
	return (0);
}

static char *handle_question_mark(t_parser *parser)
{
	char	*name;

	if (parser->str[parser->i] == '?')
	{
		name = gc_strdup(get_gc(), "?");
		parser->i++;
	}
	else
		name = gc_strdup(get_gc(), "$");
	return (name);
}
