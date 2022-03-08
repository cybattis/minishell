/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:46:20 by njennes           #+#    #+#             */
/*   Updated: 2022/03/07 11:37:17 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../libft/libft.h"

static int	check_token_order(int last, int current, t_token curr_token)
{
	if (last == TOKEN_PIPE && current == TOKEN_PIPE)
		return (0);
	if ((last == TOKEN_REDIR_OUT || last == TOKEN_REDIR_OUT_APPEND
			|| last == TOKEN_REDIR_IN || last == TOKEN_REDIR_HEREDOC)
		&& current != TOKEN_FILE)
	{
		ft_printf("Minishell: syntax error near unexpected token '%s'\n",
			curr_token.str);
		return (0);
	}
	return (1);
}

int	check_parsing_errors(t_lexer lexer)
{
	int		last_token;
	int		token;
	size_t	i;

	i = 0;
	last_token = TOKEN_EMPTY;
	while (i < lexer.count)
	{
		token = lexer.tokens[i].type;
		if (!check_token_order(last_token, token, lexer.tokens[i]))
			return (0);
		last_token = token;
		i++;
	}
	return (1);
}
