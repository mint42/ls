/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comparing_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 18:19:46 by rreedy            #+#    #+#             */
/*   Updated: 2019/03/01 20:36:39 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		compare_default(t_cmp *cmp1, t_cmp *cmp2)
{
	char	*s1;
	char	*s2;

	s1 = cmp1->cmp_string;
	s2 = cmp2->cmp_string;
	while (s1 && s2 && *s1 && *s2 && *s1 == *s2)
	{
		++s1;
		++s2;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int		compare_reverse(t_cmp *cmp1, t_cmp *cmp2)
{
	return (compare_default(cmp2, cmp1));
}

int		compare_time(t_cmp *cmp1, t_cmp *cmp2)
{
	long int		diff;

	diff = cmp2->cmp_sec - cmp1->cmp_sec;
	if (!diff)
		diff = cmp2->cmp_nsec - cmp1->cmp_nsec;
	return ((diff) ? diff : compare_default(cmp1, cmp2));
}

int		compare_time_reverse(t_cmp *cmp1, t_cmp *cmp2)
{
	return (compare_time(cmp2, cmp1));
}
