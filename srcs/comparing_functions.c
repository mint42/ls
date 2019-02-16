/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comparing_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 18:19:46 by rreedy            #+#    #+#             */
/*   Updated: 2019/02/15 17:58:32 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

//int		compare_default(t_file *f1, t_file *f2)
int		compare_default(char *f1, char *f2)
{
	return (ft_strcmp(f1, f2));
//	return (ft_strcmp(f1->name, f2->name));
}

//int		compare_reverse(t_file *f1, t_file *f2)
int		compare_reverse(char *f1, char *f2)
{
	return (ft_strcmp(f2, f1));
//	return (ft_strcmp(f2->name, f1->name));
}

//int		compare_time(t_file *f1, t_file *f2)
int		compare_time(char *f1, char *f2)
{
	return (ft_strcmp(f1, f2));
//	return (f1->time - f2->time);
}

