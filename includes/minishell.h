/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:46:20 by cybattis          #+#    #+#             */
/*   Updated: 2022/02/21 14:44:20 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "parsing.h"
# include <readline/readline.h>

# ifdef __linux__
#  include <readline/history.h>
# endif

char		*ft_get_line(void);
char		*get_prompt(void);

int			init_signal(void);
void		sig_handler(int signum);

int			execute_cmd(t_command_batch cmd_batch);

void		ft_errno_exit(int errnum);
size_t		ft_arglen(char const **args);

int			bt_echo(t_command cmd);
int			bt_exit(void);
int			bt_pwd(void);
int			bt_cd(char *path);

int			bt_export(char *var);
int			bt_env(void);
int			bt_unset(char *var);

#endif
