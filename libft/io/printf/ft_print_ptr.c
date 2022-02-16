/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:41:05 by njennes           #+#    #+#             */
/*   Updated: 2021/11/24 15:32:17 by njennes          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	ft_print_ptr(va_list *parameters_infos, int *chars_printed)
{
	long	ptr;

	ptr = (long)va_arg(*parameters_infos, size_t);
	(*chars_printed) += write(1, "0x", 2);
	(*chars_printed) += ft_putnbr_base_fd(ptr, "0123456789abcdef", 1);
}
