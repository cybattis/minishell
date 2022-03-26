/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:46:20 by njennes           #+#    #+#             */
/*   Updated: 2022/03/07 11:37:17 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stddef.h>

# define TOKEN_UNKNOWN -2
# define TOKEN_EMPTY -1
# define TOKEN_END 0
# define TOKEN_COMMAND 1
# define TOKEN_ARG 2
# define TOKEN_PIPE 3
# define TOKEN_REDIR_OUT 4
# define TOKEN_REDIR_IN 5
# define TOKEN_REDIR_OUT_APPEND 6
# define TOKEN_REDIR_HEREDOC 7
# define TOKEN_FILE 8

# define PATH_FILE 1
# define PATH_DIRECTORY 2

typedef struct s_redir
{
	int			type;
	char		*file;
}				t_redir;

typedef struct s_command
{
	int			is_piping;
	int			is_redirecting;
	int			is_builtin;
	char		*name;
	char		**args;
	t_redir		*redirections;
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
}				t_token;

typedef struct s_lexer
{
	t_token		*tokens;
	size_t		count;
}				t_lexer;

typedef struct s_err_or_charptr
{
	char		*error;
	char		*result;
}				t_err_or_charptr;

typedef struct s_err_or_char2ptr
{
	char		*error;
	char		**result;
}				t_err_or_char2ptr;

typedef struct s_err
{
	int			code;
	char		*error;
}				t_err;

char				*token_to_str(int token);
t_command_batch		parse_input(char *input);

int					error_return(char *msg, int code);
int					split_input_into_commands(char *input, t_command_batch *batch);
int					get_redirections(char *input, t_command_batch *batch);

int					is_operator_char(char c);
int					is_envchar(char c);
int					is_redirection_char(char c);
int					next_char_is_operator(char *str);
int					has_next_char(char *str);
char				*skip_spaces(char *str);
size_t				skip_quotes(char *str);
int					contains_open_spaces(char *str);
int					contains_unfinished_quotes(char *str);
char				*ask_for_quote(char *input);

char				*get_next_word_raw(char *str);
t_err_or_charptr	get_next_word(char *str, int expand_vars);
t_err_or_charptr	get_next_word_parser(t_parser *parser, int expand_vars);
t_err_or_char2ptr	get_next_word_splitted(t_parser *parser);

t_err_or_charptr	get_double_quotes(t_parser *parser);
t_err_or_charptr	get_single_quotes(t_parser *parser);

char				**get_env_var_split(t_parser *parser);
char				*get_env_var_raw(t_parser *parser);
char				*get_env_var_name(t_parser *parser);

char				*error_ambiguous_redirection(char *str);
char				*parsing_error(char *str);
char				*file_error(char *str, char *file);
int					syntax_error(t_err error);

int					is_valid_path(char *str);
int					contains_file(char *str);
int					is_absolute_path(char *str);
void				make_absolute_path(char **str);

t_parser			*strip_out_operators(char *input, t_command_batch *batch);

void				tokenize_all(t_lexer **lexers, t_parser *parsers, size_t count);

int					get_token_type(char *token, t_lexer *lexer, t_parser parser);

void				lexer_add_token(t_lexer *lexer, t_token token);
void				lexer_add_end(t_lexer *lexer);

void				populate_command_batch(t_command_batch *batch, t_lexer *lexers, size_t count);
void				destroy_command_batch(t_command_batch batch);

#endif
