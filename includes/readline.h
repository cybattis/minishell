/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:40:18 by cybattis          #+#    #+#             */
/*   Updated: 2022/02/22 16:29:47 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_H
# define READLINE_H

# ifdef __linux__
#  include <readline/history.h>
# endif
# include <readline/readline.h>
# include <readline/history.h>

void	rl_replace_line(const char *, int);

#endif