/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_create.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 17:24:38 by njennes           #+#    #+#             */
/*   Updated: 2022/01/05 17:24:41 by njennes          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

t_StringV	sv_create(const char *str)
{
	t_StringV	new;

	if (!str)
	{
		new.size = 0;
		new.chars = NULL;
		return (new);
	}
	new.size = ft_strlen(str);
	new.chars = ft_strdup(str);
	return (new);
}

t_StringV	sv_copy(const t_StringV other)
{
	t_StringV	new;

	new.size = other.size;
	new.chars = ft_strdup(other.chars);
	return (new);
}

void	sv_delete(const t_StringV stringV)
{
	if (stringV.chars)
		free(stringV.chars);
}
