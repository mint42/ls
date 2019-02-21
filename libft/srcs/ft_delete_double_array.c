/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_double_array.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 15:37:08 by rreedy            #+#    #+#             */
/*   Updated: 2019/02/20 15:55:22 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_delete_double_array(char ***double_array)
{
	if (!double_array || !*double_array)
		return ;
	while (*double_array && **double_array)
	{
		ft_strdel(*double_array);
		++(*double_array);
	}
	ft_memdel((void **)*double_array);
}
