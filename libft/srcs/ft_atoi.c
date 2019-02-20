/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 14:12:44 by rreedy            #+#    #+#             */
/*   Updated: 2018/06/04 12:41:23 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *s)
{
	int		sign;
	int		n;

	n = 0;
	sign = 1;
	while (ft_isspace(*s))
		++s;
	if (*s == '+' || *s == '-')
		sign = ((*s++ == '-') ? -1 : 1);
	while (*s && ft_isdigit(*s))
		n = n * 10 + (*s++ - 48);
	return (sign * n);
}