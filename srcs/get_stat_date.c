/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_date.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 14:58:21 by rreedy            #+#    #+#             */
/*   Updated: 2019/02/25 17:06:20 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		encode_date(time_t time, int *date_int)
{
	char	*date;

	date = ctime(&time);
	if (date[4] == 'J' && date[5] == 'a')
		*date_int = 100;
	else if (date[4] == 'J')
		*date_int = (date[6] == 'n') ? 600 : 700;
	if (date[4] == 'F')
		*date_int = 200;
	if (date[4] == 'M')
		*date_int = (date[6] == 'r') ? 300 : 500;
	if (date[4] == 'A')
		*date_int = (date[5] == 'p') ? 400 : 800;
	if (date[4] == 'S')
		*date_int = 900;
	if (date[4] == 'O')
		*date_int = 1000;
	if (date[4] == 'N')
		*date_int = 1100;
	if (date[4] == 'D')
		*date_int = 1200;
	*date_int = *date_int + ft_atoi((date[8] == ' ') ? date + 9 : date + 8);
	*date_int = *date_int + (ft_atoi(date + 20) * 10000);
}

void			get_date(t_file *file, struct stat stats)
{
	int		file_date;
	int		current_date;

	file_date = 0;
	current_date = 0;
	encode_date(stats.st_mtimespec.tv_sec, &file_date);
	encode_date(time(NULL), &current_date);
	file->date = ctime(&stats.st_mtimespec.tv_sec);
	if ((file_date - current_date) > 9400)
		ft_sprintf(&file->date, "%-8.6s%.4s", file->date + 4, file->date + 20);
	else if ((current_date - file_date) > 9400)
		ft_sprintf(&file->date, "%-8.6s%.4s", file->date + 4, file->date + 20);
	else
		ft_sprintf(&file->date, "%.12s", file->date + 4);
}
