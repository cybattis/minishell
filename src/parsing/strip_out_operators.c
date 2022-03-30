/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip_out_operators.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 13:36:24 by njennes           #+#    #+#             */
/*   Updated: 2022/03/27 13:36:25 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "core.h"
#include "libft.h"

int				is_redirection(char *str);

static t_parser	populate_parser(char *str);
static char		*skip_redir_file(char *str);
static char		*append_quotes(char *str, char **parser_str);
static char		*get_next_command(char *input);

t_parser	*strip_out_operators(char *input, t_command_batch *batch)
{
	size_t		i;
	t_parser	*parsers;

	parsers = gc_calloc(get_gc(), batch->count, sizeof (t_parser));
	i = 0;
	while (*input)
	{
		parsers[i] = populate_parser(input);
		input = get_next_command(input);
		i++;
	}
	return (parsers);
}

static t_parser	populate_parser(char *str)
{
	t_parser	parser;

	parser.str = gc_strdup(get_gc(), "");
	parser.i = 0;
	while (*str && *str != '|')
	{
		if (is_redirection_char(*str))
		{
			if (!is_redirection(str))
				while (is_redirection_char(*str))
					parser.str = gc_strappend(get_gc(), parser.str, *str++);
			else
				str = skip_redir_file(str);
		}
		else
		{
			if (*str == '\'' || *str == '"')
				str = append_quotes(str, &parser.str);
			else
				parser.str = gc_strappend(get_gc(), parser.str, *str++);
		}
	}
	return (parser);
}

static char	*skip_redir_file(char *str)
{
	t_err_or_charptr	result;

	while (is_redirection_char(*str))
		str++;
	str = skip_spaces(str);
	if (*str == '"' || *str == '\'')
		str += skip_quotes(str);
	else
		result = get_next_word(str, 0);
	str += ft_strlen(result.result);
	gc_free(get_gc(), result.result);
	return (str);
}

static char	*append_quotes(char *str, char **parser_str)
{
	size_t	i;
	char	*sub_str;

	i = skip_quotes(str);
	sub_str = gc_substr(get_gc(), str, 0, i);
	*parser_str = gc_strjoin(get_gc(), *parser_str, sub_str, FREE_BOTH);
	return (str + i);
}

static char	*get_next_command(char *input)
{
	size_t	i;

	i = 0;
	while (input[i] && input[i] != '|')
	{
		if (input[i] == '"' || input[i] == '\'')
			i += skip_quotes(&input[i]);
		else
			i++;
	}
	if (input[i] == '|')
		i++;
	return (&input[i]);
}
