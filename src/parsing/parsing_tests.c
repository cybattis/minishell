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
#include <fcntl.h>

void	start_tests()
{
	int		fd;
	char	*input;
	t_lexer	lexer;

	printf("Testing lexer:\n\n");
	fd = open("tests.txt", O_RDONLY);
	if (!fd)
		printf("Couldn't test lexer: test file does not exist");
	else
	{
		input = ft_get_next_line(fd);
		input = ft_trimr(input);
		while (input)
		{
			printf("Input: %s\n", input);
			lexer = tokenize_input(input);
			lexer_print(&lexer);
			lexer_destroy(&lexer);
			free(input);
			input = ft_get_next_line(fd);
			input = ft_trimr(input);
		}
		close(fd);
	}
}

int main()
{
	start_tests();
}
