/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:46:20 by cybattis          #+#    #+#             */
/*   Updated: 2022/04/06 10:51:50 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "parsing.h"
# include "libft.h"

# define SIGINT_HD -2
# define ERROR -1
# define BOTH_FD_SET 0
# define ONLY_OUT 1
# define ONLY_IN 2
# define NO_FD_SET 3

typedef struct s_mini
{
	t_gc			gc;
	int				last_return;
	int				is_executing;
	int				is_heredoc;
	int				has_child;
	int				argc;
	char			**argv;
	char			**env;
}	t_mini;

typedef struct s_pipe
{
	int		fd[2];
}	t_pipe;

char		*ft_get_line(void);
char		*get_prompt(void);
char		*get_git_prompt(char *path_to_git, char *current_path);
int			is_git_repo(char *path);

void		init_minishell(int argc, char **argv, char **envp);
int			init_signal(void);
void		sig_handler(int signum);

int			execute_command(t_command_batch cmd_batch);
int			execute_builtin(t_command *command);
void		execute_bin(t_command *commands);
char		**get_path(void);
void		get_child_return(int wstatus);

int			execute_pipe(t_command_batch *batch, t_pipe *pipes);
t_pipe		*init_pipe(size_t nbr);
int			redirection(t_redir *redirections);
int			redir_heredoc(t_redir redirections);

void		ft_errno_exit(void);
int			ft_print_errno(void);
void		ft_error_command(char *command);
void		ft_errno_exit_msg(char *name, int code);
int			gc_callback(void *ptr);

int			ft_error_dup(int fd);
int			clean_redirection(int *fds);
int			restore_stdfds(int std_fd[2]);
int			dup_stdfds(int std_fds[2]);

int			bt_echo(t_command *cmd);
int			bt_exit(char **args);
int			bt_pwd(void);
int			bt_cd(char *path);

int			bt_export(char **args);
int			bt_env(void);
int			bt_unset(char **args);

void		set_env_var(char *name, char *value);
void		unset_env_var(char *name);
void		update_shell_env_vars(char **envp);
int			get_empty_var_index(void);
char		*get_env(char *name);

#endif
