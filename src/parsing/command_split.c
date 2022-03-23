#include "parsing.h"
#include "libft.h"

static size_t	get_pipe_count(char *str);
static int		ends_with_pipe(char *str);
static int		contains_char(char *str);
static void		setup_piping_commands(t_command_batch *batch);

int	split_input_into_commands(char *input, t_command_batch *batch)
{
	size_t	pipe_count;

	if (ends_with_pipe(input))
		return (error_return("minishell: syntax error near unexpected token '|'", 0));
	pipe_count = get_pipe_count(input);
	if (pipe_count < ft_str_count(input, '|', FT_UNIQUE))
		return (0);
	batch->count = pipe_count;
	if (contains_char(input))
		batch->count++;
	batch->commands = gc_calloc(get_gc(), batch->count + 1, sizeof (t_command));
	if (batch->count)
		setup_piping_commands(batch);
	return (1);
}

static size_t	get_pipe_count(char *str)
{
	size_t	i;
	size_t	count;
	int		encountered_char;

	i = 0;
	count = 0;
	encountered_char = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			if (i > 0 && str[i - 1] == '|')
			{
				i++;
				continue;
			}
			if (encountered_char)
			{
				count++;
				encountered_char = 0;
			}
			else
				return (error_return("minishell: syntax error near unexpected token '|'", 0));
		}
		else if (ft_isprint(str[i]) && !ft_isspace(str[i]))
			encountered_char = 1;
		i++;
	}
	return (count);
}

static int	contains_char(char *str)
{
	size_t i;

	i = 0;
	while (str[i])
	{
		if (ft_isprint(str[i]) && !ft_isspace(str[i]))
			return (1);
		i++;
	}
	return (0);
}

static int	ends_with_pipe(char *str)
{
	char *last_pipe;

	last_pipe = ft_strrchr(str, '|');
	if (last_pipe)
		last_pipe++;
	else
		return (0);
	while (*last_pipe)
	{
		if (ft_isprint(*last_pipe) && !ft_isspace(*last_pipe))
			return (0);
		last_pipe++;
	}
	return (1);
}

static void	setup_piping_commands(t_command_batch *batch)
{
	size_t	i;

	i = 0;
	while (i < batch->count - 1)
	{
		batch->commands[i].is_piping = 1;
		i++;
	}
}
