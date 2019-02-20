/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 20:36:45 by rreedy            #+#    #+#             */
/*   Updated: 2019/01/05 20:36:49 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_pow(int n, int exponent)
{
	long	power;

	power = 1;
	while (exponent > 0)
	{
		power = power * n;
		--exponent;
	}
	return (power);
}
