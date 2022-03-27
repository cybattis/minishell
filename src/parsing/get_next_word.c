/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 13:36:07 by njennes           #+#    #+#             */
/*   Updated: 2022/03/27 13:36:14 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "core.h"

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

char	*get_next_word_raw(char *str)
{
	char	*word;
	size_t	i;

	word = gc_strdup(get_gc(), "");
	i = 0;
	while (str[i] && !ft_isspace(str[i]) && !is_operator_char(str[i]))
	{
		word = gc_strappend(get_gc(), word, str[i]);
		i++;
	}
	return (word);
}

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
