/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:46:20 by njennes           #+#    #+#             */
/*   Updated: 2022/02/16 22:17:25 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../libft/libft.h"

t_command_batch	parse_input(char *input)
{
	t_command_batch	command_batch;
	t_lexer			lexer;

	input = expand_env_vars(input);
	lexer = tokenize_input(input);
	ft_memset(&command_batch, 0, sizeof (t_command_batch));
	free(input);
	return (command_batch);
}
