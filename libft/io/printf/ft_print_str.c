/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:41:03 by njennes           #+#    #+#             */
/*   Updated: 2021/11/24 15:29:34 by njennes          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	ft_print_str(va_list *parameters_infos, int *chars_printed)
{
	char	*s;

	s = (char *)va_arg((*parameters_infos), const char *);
	if (!s)
	{
		(*chars_printed) += write(1, "(null)", 6);
		return ;
	}
	(*chars_printed) += write(1, s, ft_strlen(s));
}
