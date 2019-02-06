/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shift.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 15:35:11 by rreedy            #+#    #+#             */
/*   Updated: 2018/09/10 09:30:13 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_shift(char **s, int in, size_t size)
{
	char	*str;
	char	*cur;

	str = ft_strinit(' ', size);
	cur = *s;
	if (!str)
		return (0);
	while (cur && *cur && size)
	{
		str[in] = *cur;
		++cur;
		++in;
		--size;
	}
	ft_strdel(s);
	return (str);
}
