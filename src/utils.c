/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 14:55:35 by cybattis          #+#    #+#             */
/*   Updated: 2022/02/21 14:10:53 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

void	ft_errno_exit(int errnum)
{
	perror(strerror(errnum));
	exit(EXIT_FAILURE);
}

size_t	ft_arglen(char const **args)
{
	size_t	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}
