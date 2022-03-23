/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:33:34 by cybattis          #+#    #+#             */
/*   Updated: 2022/01/11 18:38:36 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	args;
	size_t	len;

	va_start(args, format);
	len = ft_vdprintf(1, format, args);
	va_end(args);
	return (len);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list	args;
	size_t	len;

	va_start(args, format);
	len = ft_vdprintf(fd, format, args);
	va_end(args);
	return (len);
}

int	ft_vdprintf(int fd, const char *format, va_list args)
{
	size_t		len;
	t_printf	*p;
	int			(*func[9])(t_printf *, va_list);

	p = init_data(fd, format, func);
	if (!p)
		return (-1);
	while (p->str[0])
	{
		if (p->str[0] != '%')
			print_char(p);
		else
			ft_convert(p, func, args);
		if (p->str[0] == 0)
			break ;
		p->str++;
	}
	len = p->len;
	free(p);
	return (len);
}

t_printf	*init_data(int fd, const char *s, int (**f)(t_printf *, va_list))
{
	t_printf	*p;

	f[0] = ft_int;
	f[1] = ft_uint;
	f[2] = ft_int;
	f[3] = ft_str;
	f[4] = ft_ch;
	f[5] = ft_percent;
	f[6] = ft_lower_hex;
	f[7] = ft_upper_hex;
	f[8] = ft_addr;
	p = malloc(sizeof(t_printf) * 1);
	if (!p)
		return (NULL);
	p->fd = fd;
	p->str = s;
	p->len = 0;
	p->dot = 0;
	return (p);
}

int	ft_convert(t_printf *p, int (**func)(t_printf *, va_list), va_list args)
{
	int		cs;

	p->str++;
	if (p->str[0] == 0)
		return (0);
	ft_get_flag(p);
	cs = ft_strichr("iudsc%xXp", p->str[0]);
	if (cs >= 0)
		return (func[cs](p, args));
	return (-1);
}
