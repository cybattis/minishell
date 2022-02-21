/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:19:37 by njennes           #+#    #+#             */
/*   Updated: 2022/01/05 18:25:49 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_char(va_list *parameters_infos, int *chars_printed);
void	ft_print_str(va_list *parameters_infos, int *chars_printed);
int		ft_print_integer(va_list *parameters_infos);
int		ft_print_uinteger(va_list *parameters_infos);
void	ft_print_hex(va_list *parameters_infos, int *chars_printed);
void	ft_print_hex_big(va_list *parameters_infos, int *chars_printed);
void	ft_print_ptr(va_list *parameters_infos, int *chars_printed);

static void	ft_parse_param(const char *str, va_list *parameters, int *printed)
{
	if (*str == 'c')
		ft_print_char(parameters, printed);
	else if (*str == 's')
		ft_print_str(parameters, printed);
	else if (*str == 'p')
		ft_print_ptr(parameters, printed);
	else if (*str == 'd')
		(*printed) += ft_print_integer(parameters);
	else if (*str == 'i')
		(*printed) += ft_print_integer(parameters);
	else if (*str == 'u')
		(*printed) += ft_print_uinteger(parameters);
	else if (*str == 'x')
		ft_print_hex(parameters, printed);
	else if (*str == 'X')
		ft_print_hex_big(parameters, printed);
	else
	{
		write(1, str, 1);
		(*printed)++;
	}
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		chars_printed;
	va_list	parameters_infos;

	va_start(parameters_infos, str);
	i = 0;
	chars_printed = 0;
	while (str[i])
	{
		if (str[i] != '%')
		{
			write(1, &str[i], 1);
			chars_printed++;
			i++;
		}
		else
		{
			i++;
			ft_parse_param(&str[i], &parameters_infos, &chars_printed);
			i++;
		}
	}
	va_end(parameters_infos);
	return (chars_printed);
}
