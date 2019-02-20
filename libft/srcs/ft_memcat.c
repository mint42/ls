/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 18:49:39 by rreedy            #+#    #+#             */
/*   Updated: 2018/09/09 17:50:28 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcat(void *d, const void *s, size_t dl, size_t sl)
{
	unsigned char	*cur;
	unsigned char	*cur2;

	cur = (unsigned char *)d + dl;
	cur2 = (unsigned char *)s;
	while (sl--)
		*cur++ = *cur2++;
	return (d);
}
