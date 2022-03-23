/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:09:09 by njennes           #+#    #+#             */
/*   Updated: 2021/11/05 11:13:49 by njennes          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_print(long nb, long modulo, int fd, int *printed)
{
	char	letter;
	long	result;

	letter = '0';
	result = 0;
	while (nb >= modulo)
	{
		nb = nb - modulo;
		result = result + 1;
	}
	letter = letter + result;
	(*printed) += write(fd, &letter, 1);
	if (modulo > 1)
		ft_print(nb, modulo / 10, fd, printed);
}

int	ft_putnbr_fd(long n, int fd)
{
	char	c;
	long	modulo;
	int		printed;

	printed = 0;
	if (n < 0)
	{
		printed += write(fd, "-", 1);
		n = n * -1;
	}
	if (n < 10)
	{
		c = '0' + n;
		printed += write(fd, &c, 1);
	}
	else
	{
		modulo = 10;
		while (modulo <= n)
			modulo = modulo * 10;
		modulo = modulo / 10;
		ft_print(n, modulo, fd, &printed);
	}
	return (printed);
}

int	ft_putnbr(long n)
{
	return (ft_putnbr_fd(n, 1));
}
