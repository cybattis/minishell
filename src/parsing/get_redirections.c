#include "libft.h"
#include "parsing.h"

static int		setup_redirections(char *str, t_command *command);
static size_t	get_redir_count(char *str);
static char		*get_redir_file(char *str);

int				get_redir_type(char *str);
int				is_redirection(char *str);

int	get_redirections(char *input, t_command_batch *batch)
{
	size_t	command_index;

	command_index = 0;
	while (command_index < batch->count)
	{
		setup_redirections(input, &batch->commands[command_index]);
		input = ft_strchr(input, '|') + 1;
		command_index++;
	}
	return (1);
}

static int	setup_redirections(char *str, t_command *command)
{
	size_t	i;
	size_t	j;
	size_t	redir_count;

	redir_count = get_redir_count(str);
	if (redir_count)
		command->is_redirecting = 1;
	command->redirections = gc_calloc(get_gc(), redir_count + 1, sizeof (t_redir));
	i = 0;
	j = 0;
	while (str[i] && str[i] != '|')
	{
		if (is_redirection(&str[i]))
		{
			command->redirections[j].type = get_redir_type(&str[i]);
			while (str[i] == '>' || str[i] == '<')
				i++;
			command->redirections[j].file = get_redir_file(&str[i]);
			j++;
		}
		while (str[i] == '>' || str[i] == '<')
			i++;
		if (str[i])
			i++;
	}
	return (1);
}

static char	*get_redir_file(char *str)
{
	t_err_or_charptr	file;
	char				*filename;

	str = skip_spaces(str);
	file = get_next_word(str, 1);
	if (file.error)
		return (parsing_error(file.error));
	if (contains_open_spaces(file.result))
		return (error_ambiguous_redirection(str));
	if (ft_strlen(file.result) == 0)
		return (parsing_error("minishell: :No such file or directory"));
	if (!is_absolute_path(file.result))
		make_absolute_path(&file.result);
	if (is_valid_path(file.result) == PATH_DIRECTORY)
		return (file_error("Is a directory", file.result));
	filename = ft_strrchr(file.result, '/') + 1;
	filename[-1] = 0;
	if (!is_valid_path(file.result))
		return (file_error("No such file or directory", file.result));
	filename[-1] = '/';
	return (file.result);
}

static size_t	get_redir_count(char *str)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i] && str[i] != '|')
	{
		if (is_redirection(&str[i]))
			count++;
		while (str[i] == '>' || str[i] == '<')
			i++;
		if (str[i] == '\'' || str[i] == '"')
			i += skip_quotes(&str[i]);
		if (str[i])
			i++;
	}
	return (count);
}
