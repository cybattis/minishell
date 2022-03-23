/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 16:46:04 by cybattis          #+#    #+#             */
/*   Updated: 2022/01/11 18:35:29 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_int(t_printf *p, va_list args)
{
	int	nb;
	int	len;

	nb = va_arg(args, int);
	len = ft_nbrlen(nb);
	p->len += len;
	ft_print_signe(p, nb);
	if (nb < 0 && p->flags[PRECI] > len - 1 && p->flags[MINUS] == 0)
		p->flags[FIELD]--;
	if (nb < 0 && p->flags[ZERO] == 1)
		ft_putchar_fd('-', p->fd);
	ft_print_field(p, len);
	if (p->flags[PLUS] == 1 && nb >= 0 && p->flags[ZERO] == 0)
		ft_putchar_fd('+', p->fd);
	if (nb < 0 && p->flags[ZERO] == 0)
		ft_putchar_fd('-', p->fd);
	ft_print_precision(p, len, nb);
	if (nb < 0)
		ft_uputnbr(p, -nb);
	else
		ft_putnbr(nb);
	ft_print_negfield(p);
	return (0);
}

int	ft_uint(t_printf *p, va_list args)
{
	unsigned int	nb;
	int				len;

	nb = va_arg(args, unsigned int);
	len = ft_nbrlen(nb);
	p->len += len;
	ft_print_field(p, len);
	ft_print_uprecision(p, len);
	ft_uputnbr(p, nb);
	ft_print_negfield(p);
	return (0);
}

int	ft_str(t_printf *p, va_list args)
{
	char	*s;
	int		len;

	s = va_arg(args, char *);
	if (s)
	{
		len = ft_strlen(s);
		p->len += len;
		ft_print_str_field(p, len);
		if (!ft_print_str_precision(p, s, len))
			ft_putstr(s);
		ft_print_negfield(p);
		return (0);
	}
	p->len += 6;
	ft_putstr("(null)");
	return (-1);
}

int	ft_ch(t_printf *p, va_list args)
{
	p->len++;
	ft_print_field(p, 1);
	ft_putchar_fd(va_arg(args, int), p->fd);
	ft_print_negfield(p);
	return (0);
}

int	ft_percent(t_printf *p, va_list args)
{
	(void)args;
	p->len++;
	ft_putchar_fd('%', p->fd);
	return (0);
}
