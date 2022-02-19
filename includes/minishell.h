/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:46:20 by cybattis          #+#    #+#             */
/*   Updated: 2022/02/19 18:11:11 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifdef __linux__
#  include <readline/history.h>
# endif

# include "libft.h"
# include "parsing.h"
# include <readline/readline.h>
# include <signal.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/param.h>
# include <curses.h>
# include <term.h>
# include <errno.h>

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

#endif
