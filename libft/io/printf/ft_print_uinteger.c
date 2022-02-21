/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uinteger.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:41:00 by njennes           #+#    #+#             */
/*   Updated: 2021/11/24 15:36:54 by njennes          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_uinteger(va_list *parameters_infos)
{
	unsigned int	integer;

	integer = (unsigned int)va_arg(*parameters_infos, unsigned int);
	return (ft_putnbr_fd(integer, 1));
}
