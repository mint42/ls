/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comparing_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 18:19:46 by rreedy            #+#    #+#             */
/*   Updated: 2019/11/27 15:41:09 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_cmp.h"
#include "ft_str.h"

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

int		compare_not(t_cmp *cmp1, t_cmp *cmp2)
{
	char	*s1;
	char	*s2;

	s1 = cmp1->cmp_string;
	s2 = cmp2->cmp_string;
	if (ft_strequ(s1, "."))
		return (-1);
	return ((ft_strequ(s1, "..") && !ft_strequ(s2, ".")) ? -1 : 1);
}
