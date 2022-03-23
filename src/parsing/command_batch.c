#include "parsing.h"

static void		populate_command(t_command *command, t_lexer lexer);
static int		is_builtin(char *command);
static char		**get_args(t_lexer lexer);
static size_t	get_arg_count(t_lexer *lexer);


void	populate_command_batch(t_command_batch *batch, t_lexer *lexers, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		populate_command(&batch->commands[i], lexers[i]);
		i++;
	}
}

static void	populate_command(t_command *command, t_lexer lexer)
{
	command->name = lexer.tokens[0].str;
	command->is_builtin = is_builtin(command->name);
	command->args = get_args(lexer);
}

static int	is_builtin(char *command)
{
	if (ft_strcmp(command, "echo") == 0)
		return (1);
	if (ft_strcmp(command, "exit") == 0)
		return (1);
	if (ft_strcmp(command, "export") == 0)
		return (1);
	if (ft_strcmp(command, "cd") == 0)
		return (1);
	if (ft_strcmp(command, "pwd") == 0)
		return (1);
	if (ft_strcmp(command, "unset") == 0)
		return (1);
	return (0);
}

static char	**get_args(t_lexer lexer)
{
	char	**args;
	size_t	count;
	size_t	i;
	size_t	j;

	count = get_arg_count(&lexer);
	args = gc_calloc(get_gc(), count + 1, sizeof (char **));
	i = 0;
	j = 0;
	while (i < lexer.count)
	{
		if (lexer.tokens[i].type == TOKEN_ARG)
		{
			args[j] = lexer.tokens[i].str;
			j++;
		}
		i++;
	}
	return (args);
}

static size_t get_arg_count(t_lexer *lexer)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	while (i < lexer->count)
	{
		if (lexer->tokens[i].type == TOKEN_ARG)
			count++;
		i++;
	}
	return (count);
}
