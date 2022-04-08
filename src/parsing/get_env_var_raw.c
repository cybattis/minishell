/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var_raw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 13:36:08 by njennes           #+#    #+#             */
/*   Updated: 2022/04/06 15:03:38 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"
#include "core.h"

char	*get_env_var_raw(t_parser *parser, int in_quotes)
{
	char	*var_name;
	char	*var_value;

	var_name = get_env_var_name(parser, in_quotes);
	if (ft_strlen(var_name) == 0)
		var_value = gc_strdup(get_gc(), "");
	else if (ft_strcmp(var_name, "$") == 0)
		var_value = gc_strdup(get_gc(), "$");
	else if (ft_strcmp(var_name, "?") == 0)
		var_value = gc_itoa(get_gc(), g_minishell.last_return);
	else if (ft_isdigit(*var_name))
	{
		if (*var_name == '0')
			var_value = gc_strdup(get_gc(), g_minishell.argv[0]);
		else
			var_value = gc_strdup(get_gc(), "");
	}
	else
		var_value = gc_strdup(get_gc(), get_env(var_name));
	if (!var_value)
		var_value = gc_strdup(get_gc(), "");
	gc_free(get_gc(), var_name);
	return (var_value);
}
