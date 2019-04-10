/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 16:49:01 by rreedy            #+#    #+#             */
/*   Updated: 2019/04/09 16:56:12 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPARE_H
# define COMPARE_H

# include "options.h"

# define ALL_COMPARE (OP_T | OP_R | OP_F)

typedef struct			s_cmp
{
	char				*cmp_string;
	unsigned long int	cmp_sec;
	unsigned long int	cmp_nsec;
}						t_cmp;

int						compare_default(t_cmp *cmp1, t_cmp *cmp2);
int						compare_reverse(t_cmp *cmp1, t_cmp *cmp2);
int						compare_time(t_cmp *cmp1, t_cmp *cmp2);
int						compare_time_reverse(t_cmp *cmp1, t_cmp *cmp2);
int						compare_not(t_cmp *cmp1, t_cmp *cmp2);

#endif

