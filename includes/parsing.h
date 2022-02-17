/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:46:20 by njennes           #+#    #+#             */
/*   Updated: 2022/02/16 22:17:25 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include <stddef.h>

# define TOKEN_END -2
# define TOKEN_EMPTY -1
# define TOKEN_UNKNOWN 0
# define TOKEN_COMMAND 1
# define TOKEN_ARG 2
# define TOKEN_PIPE 3
# define TOKEN_REDIR_OUT 4
# define TOKEN_REDIR_IN 5
# define TOKEN_REDIR_OUT_APPEND 6
# define TOKEN_REDIR_IN_APPEND 7
# define TOKEN_FILE 8

typedef struct s_command
{
	int			is_builtin;
	char		*name;
	char		*args;
}				t_command;

typedef struct s_command_batch
{
	t_command	*commands;
	size_t		count;
}				t_command_batch;

typedef struct s_parser
{
	size_t		i;
	char		*str;
}				t_parser;

typedef struct s_token
{
	int			type;
	char		*str;
	int			is_one_word;
}				t_token;

typedef struct s_lexer
{
	t_token		*tokens;
	size_t		count;
}				t_lexer;

t_command_batch	parse_input(char *input);

void			consume_single_quotes(t_parser *parser, t_lexer *lexer);
void			consume_double_quotes(t_parser *parser, t_lexer *lexer);
void			consume_word(t_parser *parser, t_lexer *lexer);

t_lexer			tokenize_input(char *input);
int				get_last_token_type(t_lexer *lexer);
void			lexer_add_token(t_token token, t_lexer *lexer);
void			lexer_add_end(t_lexer *lexer);
void			lexer_destroy(t_lexer *lexer);

//Debug
void			lexer_print(t_lexer *lexer);

#endif
