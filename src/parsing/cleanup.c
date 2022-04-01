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
		printf("after destroying args foorprint %d\n", gc_getfootprint(get_gc()));
		destroy_redirs(batch.commands[i].redirections);
		printf("after destroying redirs foorprint %d\n", gc_getfootprint(get_gc()));
		printf("after destroying name foorprint %d\n", gc_getfootprint(get_gc()));
		i++;
	}
	gc_free(get_gc(), batch.commands);
	printf("after destroying commands foorprint %d\n", gc_getfootprint(get_gc()));
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
	size_t	i;

	i = 0;
	while (redirs[i].type)
	{
		gc_free(get_gc(), redirs[i].file);
		i++;
	}
	gc_free(get_gc(), redirs);
}
