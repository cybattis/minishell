/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirection_ambiguous_redir.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 13:36:05 by njennes           #+#    #+#             */
/*   Updated: 2022/03/27 13:36:06 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "core.h"

int	check_for_ambiguous_redirection(char *str)
{
	t_parser			parser;
	t_err_or_char2ptr	result;
	size_t				result_size;

	parser.str = str;
	parser.i = 0;
	result = get_next_word_splitted(&parser);
	result_size = gc_strarray_size(result.result);
	gc_strarray_free(get_gc(), result.result);
	return (result_size > 1);
}
