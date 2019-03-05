/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_date.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 14:58:21 by rreedy            #+#    #+#             */
/*   Updated: 2019/03/04 18:32:44 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			get_date(t_file *file, struct stat stats)
{
	char	*date;

	date = ctime(&stats.st_mtimespec.tv_sec);
	if ((time(NULL) - stats.st_mtimespec.tv_sec) >= SECONDS_IN_6_MONTHS)
		ft_sprintf(&file->date, "%-8.6s%.4s", date + 4, date + 20);
	else if (time(NULL) < stats.st_mtimespec.tv_sec)
		ft_sprintf(&file->date, "%-8.6s%.4s", date + 4, date + 20);
	else
		ft_sprintf(&file->date, "%.12s", date + 4);
}
