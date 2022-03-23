/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:15:54 by cybattis          #+#    #+#             */
/*   Updated: 2022/01/11 18:28:28 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_negfield(t_printf *p)
{
	if (p->flags[FIELD] > 0 && p->flags[MINUS] == 1)
	{
		while (p->flags[FIELD] > 0)
		{
			ft_putchar_fd(' ', p->fd);
			p->flags[FIELD]--;
			p->len++;
		}
	}
	return (0);
}

void	ft_print_precision(t_printf *p, int len, int nb)
{
	if (nb < 0)
		len--;
	while (len < p->flags[PRECI])
	{
		ft_putchar_fd('0', p->fd);
		p->flags[FIELD]--;
		len++;
		p->len++;
	}
}

void	ft_print_uprecision(t_printf *p, unsigned int len)
{
	while (len < (unsigned int)p->flags[PRECI])
	{
		ft_putchar_fd('0', p->fd);
		len++;
		p->len++;
		p->flags[FIELD]--;
	}
}

int	ft_print_str_precision(t_printf *p, char *s, int len)
{
	int	i;

	i = 0;
	if (p->dot == 1)
	{
		if (p->flags[PRECI] < len)
			p->len -= len - p->flags[PRECI];
		while (s[i] && p->flags[PRECI] > 0)
		{
			ft_putchar_fd(s[i++], p->fd);
			p->flags[PRECI]--;
		}
		return (1);
	}
	return (0);
}
