/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_word_splitted.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 13:36:03 by njennes           #+#    #+#             */
/*   Updated: 2022/03/27 13:36:04 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "core.h"

static t_err_or_char2ptr	get_next_chars(t_parser *parser);
static size_t				append_words(t_err_or_char2ptr *result, char ***words, size_t i);

t_err_or_char2ptr	get_next_word_splitted(t_parser *parser)
{
	t_err_or_char2ptr	result;
	char				**words;
	size_t				i;

	words = gc_strarray_init(get_gc());
	words = gc_strarray_append(get_gc(), words, "");
	i = 0;
	while (parser->str[parser->i])
	{
		result = get_next_chars(parser);
		if (result.error)
		{
			gc_strarray_free(get_gc(), words);
			return (result);
		}
		if (!result.result || !gc_strarray_size(result.result))
			break ;
		i = append_words(&result, &words, i);
	}
	return ((t_err_or_char2ptr){NULL, words});
}

static size_t	append_words(t_err_or_char2ptr *result, char ***words, size_t i)
{
	size_t	j;

	(*words)[i] = gc_strjoin(get_gc(), (*words)[i], result->result[0], FREE_BOTH);
	gc_free(get_gc(), result->result[0]);
	j = 1;
	while (gc_strarray_size(result->result) && result->result[j])
	{
		(*words) = gc_strarray_append(get_gc(), *words, result->result[j]);
		gc_free(get_gc(), result->result[j++]);
		i++;
	}
	return (i);
}

static t_err_or_char2ptr	get_next_chars(t_parser *parser)
{
	t_err_or_char2ptr	result;
	t_err_or_charptr	intermediate;

	ft_memset(&result, 0, sizeof (t_err_or_char2ptr));
	ft_memset(&intermediate, 0, sizeof (t_err_or_charptr));
	if (parser->str[parser->i] == '\'')
		intermediate = get_single_quotes(parser);
	else if (parser->str[parser->i] == '"')
		intermediate = get_double_quotes(parser);
	else if (parser->str[parser->i] == '$')
		result.result = get_env_var_split(parser);
	else if (ft_isspace(parser->str[parser->i])
			 || is_operator_char(parser->str[parser->i]))
		result.result = NULL;
	else
	{
		intermediate.result = gc_substr(get_gc(), parser->str, parser->i, 1);
		parser->i++;
	}
	if (intermediate.result)
		result.result = gc_strarray_fromstr(get_gc(), intermediate.result);
	if (intermediate.error)
		result.error = intermediate.error;
	return (result);
}
