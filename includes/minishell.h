/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:46:20 by cybattis          #+#    #+#             */
/*   Updated: 2022/03/05 15:09:14 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "parsing.h"
# include "libft.h"
# include <termios.h>

typedef struct s_app
{
	t_gc				gc;
	int					last_return;
	char				**base_env;
	struct termios		og_termios;
}	t_app;

extern t_app	g_minishell;

t_gc		*get_gc(void);

char		*ft_get_line(void);
char		*get_prompt(void);

void		init_minishell(char **envp);
int			init_signal(void);
void		sig_handler(int signum);

int			execute_command(t_command_batch cmd_batch);
void		execute_bin(t_command *commands);
char		**get_path(void);

int			execute_pipe(int *fds, t_command *command);
int			redirection(t_redir *redirections);

int			ft_errno(int errnum);
void		ft_error_command(char *command);
void		ft_errno_exit(int errnum);
size_t		ft_arglen(char const **args);
int			gc_callback(void *ptr);

int			execute_builtin(t_command *command);
int			bt_echo(t_command *cmd);
int			bt_exit(void);
int			bt_pwd(void);
int			bt_cd(char *path);

int			bt_export(char **args);
int			bt_env(void);
int			bt_unset(char **args);

void		set_env_var(char *name, char *value);
void		unset_env_var(char *name);
void		update_shell_env_vars(void);

void 		enableRawMode(struct termios og_termios);
void 		disableRawMode(struct termios og_termios);

#endif
