/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:41:11 by njennes           #+#    #+#             */
/*   Updated: 2021/11/25 17:28:39 by njennes          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	ft_print_hex(va_list *parameters_infos, int *chars_printed)
{
	unsigned int	integer;

	integer = (unsigned int)va_arg(*parameters_infos, unsigned int);
	(*chars_printed) += ft_putnbr_base_fd(integer, "0123456789abcdef", 1);
}
