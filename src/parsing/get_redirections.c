/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 13:36:16 by njennes           #+#    #+#             */
/*   Updated: 2022/03/27 13:36:17 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "core.h"

static t_err	setup_redirections(char *str, t_command *command);
static char		*get_redir_file(char *str);
static char		*get_heredoc_delimiter(char *str);

int				get_redir_type(char *str);
int				is_redirection(char *str);
int				check_for_ambiguous_redirection(char *str);
int				allocate_redirs(t_command *command, char *str);
size_t			skip_redir_chars(char *str, size_t i);
size_t			get_to_next_char(char *str, size_t i);

int	get_redirections(char *input, t_command_batch *batch)
{
	size_t	command_index;
	t_err	result;

	command_index = 0;
	while (command_index < batch->count)
	{
		result = setup_redirections(input, &batch->commands[command_index]);
		if (result.error)
		{
			batch->count = 0;
			return (syntax_error(result));
		}
		input = ft_strchr(input, '|') + 1;
		command_index++;
	}
	return (1);
}

static t_err	setup_redirections(char *str, t_command *command)
{
	size_t	i;
	size_t	j;

	if (!allocate_redirs(command, str))
		return ((t_err){.code = 1, .error = NULL});
	i = 0;
	j = 0;
	while (str[i] && str[i] != '|')
	{
		if (is_redirection(&str[i]))
		{
			command->redirections[j].type = get_redir_type(&str[i]);
			i = skip_redir_chars(str, i);
			if (!has_next_char(&str[i]) || next_char_is_operator(&str[i]))
				return ((t_err){0, &str[i]});
			if (command->redirections[j].type == TOKEN_REDIR_HEREDOC)
				command->redirections[j].file = get_heredoc_delimiter(&str[i]);
			else
				command->redirections[j].file = get_redir_file(&str[i]);
			j++;
		}
		i = skip_redir_chars(str, i);
		i = get_to_next_char(str, i);
	}
	return ((t_err){1, NULL});
}

static char	*get_redir_file(char *str)
{
	t_err_or_charptr	file;
	char				*filename;

	str = skip_spaces(str);
	file = get_next_word(str, 1);
	if (file.error)
		return (parsing_error(file.error, NULL));
	if (check_for_ambiguous_redirection(str))
		return (error_ambiguous_redirection(str, file.result));
	if (ft_strlen(file.result) == 0)
		return (parsing_error("minishell: :No such file or directory",
				file.result));
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

static char	*get_heredoc_delimiter(char *str)
{
	char	*delimiter;

	str = skip_spaces(str);
	delimiter = get_next_word_raw(str);
	return (delimiter);
}
