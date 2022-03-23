#include "libft.h"
#include "parsing.h"

static char	*extract_first_word(char *str);

char	*get_env_var_first_word(t_parser *parser)
{
	char	*var_value;
	char	*first_word;

	var_value = get_env_var_raw(parser);
	first_word = extract_first_word(var_value);
	gc_free(get_gc(), var_value);
	return (first_word);
}

static char	*extract_first_word(char *str)
{
	char	*result;
	size_t	size;

	size = 0;
	str = skip_spaces(str);
	while (str[size] && !ft_isspace(str[size]))
		size++;
	result = gc_substr(get_gc(), str, 0, size);
	return (result);
}
