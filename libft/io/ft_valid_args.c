/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_valid_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 17:49:56 by                   #+#    #+#             */
/*   Updated: 2022/01/25 17:54:18 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_format_valid_a(char *format, char *str);
int	ft_format_valid_s(char *format, char *str);
int	ft_format_valid_d(char *format, char *str);
int	ft_format_valid_f(char *format, char *str);
int	ft_format_valid_c(char *str);

static int	valid_format(char *format, char *str)
{
	if (*format == 'a')
		return (ft_format_valid_a(format + 1, str));
	else if (*format == 's')
		return (ft_format_valid_s(format + 1, str));
	else if (*format == 'd')
		return (ft_format_valid_d(format + 1, str));
	else if (*format == 'f')
		return (ft_format_valid_f(format + 1, str));
	else if (*format == 'c')
		return (ft_format_valid_c(str));
	else
		return (FT_FALSE);
}

int	ft_valid_args(size_t argc, char **argv, char *format)
{
	size_t	i;
	size_t	arg;

	if (argc - 1 != ft_str_count(ft_trim(format), ' ', FT_GROUPS) + 1)
		return (FT_FALSE);
	i = 0;
	arg = 1;
	while (format[i])
	{
		if (!valid_format(&format[i + 1], argv[arg]))
			return (FT_FALSE);
		while (format[i] && format[i + 1] != '%')
			i++;
		arg++;
	}
	return (FT_TRUE);
}
