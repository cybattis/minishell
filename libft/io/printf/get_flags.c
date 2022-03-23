/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:34:37 by cybattis          #+#    #+#             */
/*   Updated: 2021/11/30 17:02:20 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_field_size(t_printf *p);
static void	init_flags(t_printf *p);

int	ft_get_flag(t_printf *p)
{
	int	f;

	init_flags(p);
	f = ft_strichr("-# +0", p->str[0]);
	while (f >= 0)
	{
		p->flags[f] = 1;
		p->str++;
		f = ft_strichr("-# +0", p->str[0]);
	}
	ft_field_size(p);
	return (0);
}

static int	ft_field_size(t_printf *p)
{
	while (ft_isdigit(p->str[0]) || p->str[0] == '.')
	{
		if (p->str[0] == '.')
		{
			p->dot = 1;
			p->str++;
			while (ft_isdigit(p->str[0]))
			{
				p->flags[PRECI] = p->flags[PRECI] * 10 + (p->str[0] - '0');
				p->str++;
			}
		}
		else
		{
			p->flags[FIELD] = p->flags[FIELD] * 10 + (p->str[0] - '0');
			p->str++;
		}
	}
	return (0);
}

static void	init_flags(t_printf *p)
{
	int	i;

	i = 0;
	while (i < 7)
		p->flags[i++] = 0;
}
