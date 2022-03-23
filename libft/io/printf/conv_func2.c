/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_func2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 17:41:07 by cybattis          #+#    #+#             */
/*   Updated: 2022/01/11 18:37:31 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_lower_hex(t_printf *p, va_list args)
{
	t_data	hex;

	hex.nb = va_arg(args, unsigned int);
	hex.len = ft_nbrlen_base(hex.nb, 16);
	p->len += hex.len;
	ft_print_hex_field(p, "0x", hex);
	ft_print_uprecision(p, hex.len);
	ft_putnbr_hex(p, hex.nb, "0123456789abcdef", 16);
	ft_print_negfield(p);
	return (0);
}

int	ft_upper_hex(t_printf *p, va_list args)
{
	t_data	hex;

	hex.nb = va_arg(args, unsigned int);
	hex.len = ft_nbrlen_base(hex.nb, 16);
	p->len += hex.len;
	ft_print_hex_field(p, "0X", hex);
	ft_print_uprecision(p, hex.len);
	ft_putnbr_hex(p, hex.nb, "0123456789ABCDEF", 16);
	ft_print_negfield(p);
	return (0);
}

int	ft_addr(t_printf *p, va_list args)
{
	size_t	nb;
	int		len;

	nb = va_arg(args, size_t);
	len = ft_nbrlen_base(nb, 16);
	p->len += len + 2;
	p->flags[FIELD] -= 2;
	ft_print_field(p, len);
	ft_putstr("0x");
	ft_putnbr_hex(p, nb, "0123456789abcdef", 16);
	ft_print_negfield(p);
	return (0);
}
