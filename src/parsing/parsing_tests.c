/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tests.c                                    :+:      :+:    :+:   */
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

void	print_test(char *name)
{
	size_t	printed;
	size_t	need_to_print;

	printf("\n\n");
	need_to_print = printf("========================================\n");
	printed = printf("|[TEST]  :  %s", name);
	while (printed < need_to_print - 2)
		printed += printf(" ");
	printf("|\n");
	printf("========================================\n");
	printf("\n\n");
}

void	start_tests()
{
	int		fd;
	char	*input;
	t_lexer	lexer;

	print_test("Lexer");
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

	char	*expanded;
	print_test("Var Expansions");
	fd = open("tests.txt", O_RDONLY);
	if (!fd)
		printf("Couldn't test Var Expansions: test file does not exist");
	else
	{
		input = ft_get_next_line(fd);
		input = ft_trimr(input);
		while (input)
		{
			printf("Input: %s\n", input);
			expanded = expand_env_vars(input);
			printf("Expanded: %s\n", expanded);
			free(input);
			free(expanded);
			input = ft_get_next_line(fd);
			input = ft_trimr(input);
		}
		close(fd);
	}

	print_test("Var Expansions && Lexer");
	fd = open("tests.txt", O_RDONLY);
	if (!fd)
		printf("Couldn't test Var Expansions && Lexer: test file does not exist");
	else
	{
		input = ft_get_next_line(fd);
		input = ft_trimr(input);
		while (input)
		{
			printf("Input: %s\n", input);
			expanded = expand_env_vars(input);
			lexer = tokenize_input(expanded);
			lexer_print(&lexer);
			lexer_destroy(&lexer);
			free(input);
			free(expanded);
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
