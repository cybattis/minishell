/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:46:20 by cybattis          #+#    #+#             */
/*   Updated: 2022/03/21 15:47:35 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "parsing.h"
# include "libft.h"
# include <termios.h>

typedef struct s_mini
{
	t_gc			gc;
	int				last_return;
	int				is_executing;
	char			**base_env;
	struct termios	termios;
}	t_mini;

typedef struct s_pipe
{
	int fd[2];
}	t_pipe;

extern t_mini	g_minishell;

t_gc		*get_gc(void);

char		*ft_get_line(void);
char		*get_prompt(void);
char		*get_git_prompt(char *path_to_git, char *current_path);
int			is_git_repo(char *path);

void		init_minishell(char **envp);
int			init_signal(void);
void		sig_handler(int signum);
int			init_signal_child(void);
void		sig_handler_child(int signum);

int			execute_command(t_command_batch cmd_batch);
void		execute_bin(t_command *commands);
int			clean_fds(int save_fd[2]);
char		**get_path(void);

int			execute_pipe(t_command_batch *batch, t_pipe *pipes);
t_pipe		*init_pipe(size_t nbr);
int			redirection(t_redir *redirections);
int			redir_heredoc(t_redir redirections);

int			ft_print_errno(void);
void		ft_error_command(char *command);
void		ft_errno_exit(int errnum);
size_t		ft_arglen(char const **args);
int			gc_callback(void *ptr);

int			execute_builtin(t_command *command);
int			bt_echo(t_command *cmd);
int			bt_exit(char **args);
int			bt_pwd(void);
int			bt_cd(char *path);

int			bt_export(char **args);
int			bt_env(void);
int			bt_unset(char **args);

void		set_env_var(char *name, char *value);
void		unset_env_var(char *name);
void		update_shell_env_vars(void);
int			get_empty_var_index(void);

void		enable_alt_termmode(void);
void		disable_alt_termmode(void);

#endif
