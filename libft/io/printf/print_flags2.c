/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_flags2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:17:34 by cybattis          #+#    #+#             */
/*   Updated: 2022/01/11 18:29:22 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_signe(t_printf *p, int nb)
{
	if (p->flags[SPACE] == 1 && p->flags[PLUS] == 0 && nb >= 0)
		ft_putchar_fd(' ', p->fd);
	else if (p->flags[PLUS] == 1 && nb >= 0 && p->flags[ZERO] == 1)
		ft_putchar_fd('+', p->fd);
	else if (p->flags[PLUS] == 1 && nb >= 0 && p->flags[ZERO] == 0)
		;
	else
		return (1);
	p->flags[FIELD]--;
	p->len++;
	return (0);
}

void	ft_print_field(t_printf *p, int len)
{
	if (p->flags[MINUS] == 0)
	{
		while (p->flags[FIELD] > ft_max(p->flags[PRECI], len))
		{
			if (p->flags[ZERO] == 1 && p->flags[PRECI] == 0)
				ft_putchar_fd('0', p->fd);
			else
				ft_putchar_fd(' ', p->fd);
			p->flags[FIELD]--;
			p->len++;
		}
	}
	p->flags[FIELD] -= len;
}

void	ft_print_str_field(t_printf *p, int len)
{
	int	max;

	max = len;
	if (p->flags[PRECI] > 0 && p->flags[PRECI] < len)
		max = p->flags[PRECI];
	if (p->flags[MINUS] == 0)
	{
		while (p->flags[FIELD] > max)
		{
			if (p->flags[ZERO] == 1 && p->flags[PRECI] == 0)
				ft_putchar_fd('0', p->fd);
			else
				ft_putchar_fd(' ', p->fd);
			p->flags[FIELD]--;
			p->len++;
		}
	}
	else
		p->flags[FIELD] -= max;
}

int	ft_print_hex_field(t_printf *p, char *alt, t_data hex)
{
	if (p->flags[ALT] == 1 && hex.nb > 0)
	{
		p->flags[FIELD] -= 2;
		if (p->flags[ZERO] == 1)
		{
			ft_putstr_fd(alt, p->fd);
			ft_print_field(p, hex.len);
		}
		else if (p->flags[ALT] == 1)
		{
			ft_print_field(p, hex.len);
			ft_putstr_fd(alt, p->fd);
		}
		p->len += 2;
	}
	else
		ft_print_field(p, hex.len);
	return (0);
}
