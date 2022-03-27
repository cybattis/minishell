/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 15:21:18 by njennes           #+#    #+#             */
/*   Updated: 2022/03/27 15:21:19 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

typedef struct s_mini	t_mini;
typedef struct s_gc		t_gc;

extern t_mini			g_minishell;

t_gc					*get_gc(void);

#endif
