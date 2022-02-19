/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:46:20 by njennes           #+#    #+#             */
/*   Updated: 2022/02/16 22:17:25 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../libft/libft.h"

char	*get_var(char *name)
{
	char	*value;

	value = getenv(name);
	free(name);
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
	if ((c >= 'A' && c <= 'Z') || c == '_' || ft_isdigit(c))
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
//TODO: append blocks of characters that doesn't need expansion instead of adding them one by one
char	*expand_env_vars(char *str)
{
	size_t	i;
	char	*env_var;
	char	*new_str;
	char	quote;

	new_str = ft_strdup(""); //TODO: replace with gc_strdup
	quote = 0;
	i = 0;
	while (str[i])
	{
		quote = check_for_quote(quote, str[i]);
		if (quote != '\'' && str[i] == '$' && is_envchar(str[i + 1]))
		{
			i++;
			env_var = get_var(ft_substr(str, i,get_env_var_len(&str[i])));
			new_str = ft_strjoin(new_str, env_var, 1); //TODO: Replace with gc_strjoin
			while (str[i] && is_envchar(str[i + 1]))
				i++;
		}
		else
			new_str = ft_strappend(new_str, str[i]); //TODO: Replace with gc_strappend
		i++;
	}
	return (new_str);
}
