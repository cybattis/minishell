#include "libft.h"
#include "parsing.h"
#include "core.h"
#include "readline.h"
#include "minishell.h"

static char	*get_line(char *input);

char	*ask_for_quote(char *input)
{
	char	*line;

	while (contains_unfinished_quotes(input))
	{
		line = get_line(input);
		if (!line)
			return (gc_strdup(get_gc(), ""));
		input = gc_strappend(get_gc(), input, '\n');
		input = gc_strjoin(get_gc(), input, line, FREE_FIRST);
		free(line);
	}
	add_history(input);
	return (input);
}

static char	*get_line(char *input)
{
	char	*line;

	line = readline("> ");
	if (!line)
	{
		ft_dprintf(STDERR_FILENO, "minishell: unexpected EOF while looking for matching `%c'\n"
								  "minishell: syntax error: unexpected end of file\n",
				contains_unfinished_quotes(input));
		add_history(input);
		gc_free(get_gc(), input);
		return (NULL);
	}
	return (line);
}
