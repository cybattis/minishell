/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:46:20 by njennes           #+#    #+#             */
/*   Updated: 2022/03/05 15:28:37 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include "minishell.h"

char	*get_var(char *name)
{
	char	*value;

	value = getenv(name);
	gc_free(get_gc(), name);
	return (value);
}

char	check_for_quote(char quote, char current)
{
	if (!quote)
	{
		if (current == '"')
			quote = '"';
		else if (current == '\'')
			quote = '\'';
	}
	else
	{
		if (quote == '"' && current == '"')
			quote = 0;
		else if (quote == '\'' && current == '\'')
			quote = 0;
	}
	return (quote);
}

int	is_envchar(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

size_t	get_env_var_len(char *str)
{
	size_t	len;

	len = 0;
	while (str[len] && is_envchar(str[len]))
		len++;
	return (len);
}

//TODO: Make this faster by treating chunks of chars
//TODO: append blocks of characters that doesn't need expansion instead
// of adding them one by one
char	*expand_env_vars(char *str)
{
	size_t	i;
	char	*env_var;
	char	*new_str;
	char	quote;

	new_str = gc_strdup(get_gc(), "");
	quote = 0;
	i = 0;
	while (str[i])
	{
		quote = check_for_quote(quote, str[i]);
		if (quote != '\'' && str[i] == '$' && is_envchar(str[i + 1]))
		{
			i++;
			env_var = get_var(gc_substr(get_gc(), str, i,
						get_env_var_len(&str[i])));
			new_str = gc_strjoin(get_gc(), new_str, env_var, 1);
			while (str[i] && is_envchar(str[i + 1]))
				i++;
		}
		else
			new_str = gc_strappend(get_gc(), new_str, str[i]);
		i++;
	}
	return (new_str);
}
