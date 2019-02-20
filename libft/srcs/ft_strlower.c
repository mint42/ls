/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlower.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 09:13:22 by rreedy            #+#    #+#             */
/*   Updated: 2018/08/16 09:13:24 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strlower(char *s)
{
	char	*cur;

	cur = s;
	while (cur && *cur)
	{
		if (ft_isupper(*cur))
			*cur = ft_tolower(*cur);
		++cur;
	}
	return (s);
}
