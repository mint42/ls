/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_cmp.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 15:37:58 by rreedy            #+#    #+#             */
/*   Updated: 2019/11/27 15:41:20 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_CMP_H
# define STRUCT_CMP_H

# include "struct_options.h"

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
