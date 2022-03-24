#include "libft.h"
#include "parsing.h"
#include "core.h"

static char	*extract_next_word(t_parser *parser);

char	**get_env_var_split(t_parser *parser)
{
	t_parser	var_value;
	char		*next_word;
	char		**array;

	var_value.str = get_env_var_raw(parser);
	var_value.i = 0;
	array = gc_strarray_init(get_gc());
	next_word = extract_next_word(&var_value);
	while (next_word)
	{
		array = gc_strarray_append(get_gc(), array, next_word);
		gc_free(get_gc(), next_word);
		next_word = extract_next_word(&var_value);
	}
	return (array);
}

static char	*extract_next_word(t_parser *parser)
{
	char	*result;
	size_t	size;

	size = 0;
	parser->str = skip_spaces(parser->str);
	while (parser->str[size] && !ft_isspace(parser->str[size]))
		size++;
	if (size == 0)
		return (NULL);
	result = gc_substr(get_gc(), parser->str, 0, size);
	parser->str += size;
	return (result);
}
