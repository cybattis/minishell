/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 13:35:58 by njennes           #+#    #+#             */
/*   Updated: 2022/03/27 13:35:59 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "core.h"
#include "minishell.h"

static char	*handle_special_var(t_parser *parser, int in_quotes);
static char	*handle_program_arguments(t_parser *parser);

char	*get_env_var_name(t_parser *parser, int in_quotes)
{
	char	*name;

	parser->i++;
	if (!is_envchar(parser->str[parser->i]))
		return (handle_special_var(parser, in_quotes));
	if (ft_isdigit(parser->str[parser->i]))
		return (handle_program_arguments(parser));
	name = gc_strdup(get_gc(), "");
	while (is_envchar(parser->str[parser->i]))
	{
		name = gc_strappend(get_gc(), name, parser->str[parser->i]);
		parser->i++;
	}
	return (name);
}

int	is_envchar(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

static char	*handle_special_var(t_parser *parser, int in_quotes)
{
	char	*name;

	if (parser->str[parser->i] == '?')
	{
		name = gc_strdup(get_gc(), "?");
		parser->i++;
	}
	else if (ft_isspace(parser->str[parser->i]) || !parser->str[parser->i]
				|| (in_quotes && parser->str[parser->i] == '"'))
		name = gc_strdup(get_gc(), "$");
	else
		name = gc_strdup(get_gc(), "");
	return (name);
}

static char	*handle_program_arguments(t_parser *parser)
{
	char	*name;

	if (ft_atoi(&parser->str[parser->i]) < g_minishell.argc)
		name = gc_substr(get_gc(), parser->str, parser->i, 1);
	else
		name = gc_strdup(get_gc(), "");
	parser->i++;
	return (name);
}
