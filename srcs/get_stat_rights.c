/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_stats_rights.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:12:06 by rreedy            #+#    #+#             */
/*   Updated: 2019/03/05 18:18:29 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		get_file_type(t_file *file, int mode)
{
	if (S_ISBLK(mode))
		file->rights[0] = 'b';
	else if (S_ISCHR(mode))
		file->rights[0] = 'c';
	else if (S_ISDIR(mode))
		file->rights[0] = 'd';
	else if (S_ISLNK(mode))
		file->rights[0] = 'l';
	else if (S_ISFIFO(mode))
		file->rights[0] = 'p';
	else if (S_ISSOCK(mode))
		file->rights[0] = 's';
}

void			get_rights(t_file *file, struct stat stats)
{
	unsigned int	bits;
	int				i;

	i = 10;
	bits = (stats.st_mode) & (S_IRWXU | S_IRWXG | S_IRWXO);
	file->rights = ft_strdup("-rwxrwxrwx");
	while (--i >= 0)
		if (!((bits >> i) & 1))
			file->rights[9 - i] = '-';
	if (S_ISUID & stats.st_mode)
		file->rights[3] = (file->rights[3] == '-') ? 'S' : 's';
	if (S_ISGID & stats.st_mode)
		file->rights[6] = (file->rights[6] == '-') ? 'S' : 's';
	if (S_ISVTX & stats.st_mode)
		file->rights[9] = (file->rights[9] == '-') ? 'T' : 't';
	get_file_type(file, stats.st_mode);
}
