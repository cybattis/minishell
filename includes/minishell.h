/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:46:20 by cybattis          #+#    #+#             */
/*   Updated: 2022/02/21 19:03:44 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "parsing.h"
# include "libft.h"

extern t_gc	g_gc;

char		*ft_get_line(void);
char		*get_prompt(void);

int			init_signal(void);
void		sig_handler(int signum);

int			execute_command(t_command_batch cmd_batch);

void		ft_error_command(char *command);
void		ft_errno_exit(int errnum);
size_t		ft_arglen(char const **args);
int			gc_callback(void *ptr);

int			bt_echo(t_command *cmd);
int			bt_exit(void);
int			bt_pwd(void);
int			bt_cd(char *path);

int			bt_export(char **args);
int			bt_env(void);
int			bt_unset(char *var);

#endif
