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

#include "parsing.h"
#include "libft.h"
#include "minishell.h"

t_command_batch	parse_input(char *input)
{
	t_command_batch	command_batch;
	t_lexer			lexer;

	lexer = tokenize_input(input);
	lexer_print(&lexer);
	ft_memset(&command_batch, 0, sizeof (t_command_batch));
	if (!check_parsing_errors(lexer))
		return (command_batch);
	ft_printf("heyy\n");
	create_command_batch(lexer, &command_batch);
	lexer_destroy(&lexer);
	return (command_batch);
}
