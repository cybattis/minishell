/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:41:18 by njennes           #+#    #+#             */
/*   Updated: 2021/11/24 15:06:40 by njennes          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_char(va_list *parameters_infos, int *chars_printed)
{
	char	c;

	c = (char)va_arg(*parameters_infos, int);
	write(1, &c, 1);
	(*chars_printed)++;
}
