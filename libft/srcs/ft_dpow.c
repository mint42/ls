/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dpow.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 20:37:00 by rreedy            #+#    #+#             */
/*   Updated: 2019/01/05 20:37:07 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_dpow(int n, int exponent)
{
	double	power;

	power = 1;
	while (exponent > 0)
	{
		power = power * n;
		--exponent;
	}
	return (power);
}
