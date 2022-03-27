/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 13:35:49 by njennes           #+#    #+#             */
/*   Updated: 2022/03/27 13:35:50 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include "core.h"

static void	destroy_args(char **args);
static void	destroy_redirs(t_redir *redirs);

void	destroy_command_batch(t_command_batch batch)
{
	size_t	i;

	i = 0;
	while (i < batch.count)
	{
		destroy_args(batch.commands[i].args);
		destroy_redirs(batch.commands[i].redirections);
		gc_free(get_gc(), batch.commands[i].name);
		i++;
	}
	gc_free(get_gc(), batch.commands);
}

static void	destroy_args(char **args)
{
	size_t	i;

	i = 0;
	while (args[i])
	{
		gc_free(get_gc(), args[i]);
		i++;
	}
	gc_free(get_gc(), args);
}

static void	destroy_redirs(t_redir *redirs)
{
	gc_free(get_gc(), redirs);
}
