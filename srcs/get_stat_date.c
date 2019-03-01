/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_date.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 14:58:21 by rreedy            #+#    #+#             */
/*   Updated: 2019/02/28 18:22:15 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		encode_date(time_t time, long long int *num)
{
	char	*date;

	date = ctime(&time);
	if (date[4] == 'J' && date[5] == 'a')
		*num = 100000000;
	else if (date[4] == 'J')
		*num = (date[6] == 'n') ? 600000000 : 700000000;
	else if (date[4] == 'F')
		*num = 200000000;
	else if (date[4] == 'M')
		*num = (date[6] == 'r') ? 300000000 : 500000000;
	else if (date[4] == 'A')
		*num = (date[5] == 'p') ? 400000000 : 800000000;
	else if (date[4] == 'S')
		*num = 900000000;
	else if (date[4] == 'O')
		*num = 1000000000;
	else
		*num = (date[4] == 'N') ? 1100000000 : 1200000000;
	*num = *num + (ft_atoi(date + 20) * 10000000000);
	*num = *num + ((ft_atoi((date[8] == ' ') ? date + 9 : date + 8)) * 1000000);
	*num = *num + (ft_atoi(date + 11) * 10000);
	*num = *num + (ft_atoi(date + 14) * 100);
	*num = *num + (ft_atoi(date + 17));
}

void			get_date(t_file *file, struct stat stats)
{
	long long int		file_date;
	long long int		current_date;

	file_date = 0;
	current_date = 0;
	encode_date(stats.st_mtimespec.tv_sec, &file_date);
	encode_date(time(NULL), &current_date);
	file->date = ctime(&stats.st_mtimespec.tv_sec);
	if ((current_date - file_date) > 9400000000)
		ft_sprintf(&file->date, "%-8.6s%.4s", file->date + 4, file->date + 20);
	else if (current_date < file_date)
		ft_sprintf(&file->date, "%-8.6s%.4s", file->date + 4, file->date + 20);
	else
		ft_sprintf(&file->date, "%.12s", file->date + 4);
}
