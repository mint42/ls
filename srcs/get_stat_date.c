/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_date.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 14:58:21 by rreedy            #+#    #+#             */
/*   Updated: 2019/04/15 04:30:19 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stats.h"
#include "options.h"
#include "file.h"
#include "ft_printf.h"
#include <time.h>
#include <sys/stat.h>

void			get_date(t_file *file, struct stat stats, int flags)
{
	char	*date;

	date = ctime(&stats.st_mtimespec.tv_sec);
	if (flags & OP_BIGT)
		ft_sprintf(&file->date, "%.20s", date + 4);
	else if ((time(NULL) - stats.st_mtimespec.tv_sec) >= SECONDS_IN_6_MONTHS)
		ft_sprintf(&file->date, "%-8.6s%.4s", date + 4, date + 20);
	else if (time(NULL) < stats.st_mtimespec.tv_sec)
		ft_sprintf(&file->date, "%-8.6s%.4s", date + 4, date + 20);
	else
		ft_sprintf(&file->date, "%.12s", date + 4);
}
