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

#include "../libft.h"

int	ft_format_valid_a(char *format, char *str)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = INT64_MAX;
	if (ft_isdigit(format[i]))
		len = ft_atoi(&format[i]);
	if (ft_strlen(str) > len)
		return (FT_FALSE);
	return (FT_TRUE);
}

int	ft_format_valid_s(char *format, char *str)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = INT64_MAX;
	if (ft_isdigit(format[i]))
		len = ft_atoi(&format[i]);
	while (str[i] && len && ft_isalpha(str[i]))
	{
		len--;
		i++;
	}
	if (str[i] != 0 || i == 0)
		return (FT_FALSE);
	return (FT_TRUE);
}

int	ft_format_valid_d(char *format, char *str)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = INT64_MAX;
	if (ft_isdigit(format[i]))
		len = ft_atoi(&format[i]);
	if (str[i] == '-' && len > 0)
	{
		len--;
		i++;
		if (!ft_isdigit(str[i]))
			return (FT_FALSE);
	}
	while (str[i] && len && ft_isdigit(str[i]))
	{
		len--;
		i++;
	}
	if (str[i] != 0 || i == 0)
		return (FT_FALSE);
	return (FT_TRUE);
}

int	ft_format_valid_f(char *format, char *str)
{
	size_t	i;
	size_t	len1;
	size_t	len2;

	i = 0;
	len1 = INT64_MAX;
	len2 = INT64_MAX;
	if (ft_isdigit(format[i]))
		len1 = ft_atoi(&format[i]);
	while (ft_isdigit(format[i]))
		i++;
	i++;
	len2 = ft_atoi(&format[i]);
	i = 0;
	while (str[i] && len1 && ft_isdigit(str[i]))
	{
		len1--;
		i++;
	}
	if (ft_isdigit(str[i]))
		return (FT_FALSE);
	if (!(str[i] == ',' || str[i] == '.'))
		return (FT_FALSE);
	i++;
	while (str[i] && len2 && ft_isdigit(str[i]))
	{
		len2--;
		i++;
	}
	if (str[i] != 0 || i == 0)
		return (FT_FALSE);
	return (FT_TRUE);
}

int	ft_format_valid_c(char *str)
{
	if (ft_strlen(str) != 1)
		return (FT_FALSE);
	return (FT_TRUE);
}
