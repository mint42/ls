/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_long.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 16:21:31 by rreedy            #+#    #+#             */
/*   Updated: 2019/02/01 19:22:18 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char		*get_rights(struct stat stats)
{
	char			*rights;
	unsigned int	bits;
	int				i;

	i = 10;
	bits = (stats.st_mode) & (S_IRWXU | S_IRWXG | S_IRWXO);
	rights = ft_strdup("-rwxrwxrwx");
	while (--i >= 0)
		if (!((bits >> i) & 1))
			rights[9 - i] = '-';
	return (rights);
}

static char		*get_date(struct stat stats)
{
	char	*date;

	date = ctime(&stats.st_mtime);
	if ((time(NULL) - stats.st_mtime) > SECONDS_IN_6_MONTHS)
		ft_sprintf(&date, "%-8.6s%.4s", date + 4, date + 20);
	else
		ft_sprintf(&date, "%.12s", date + 4);
	return (date);
}

static void		get_info(t_file *file)
{
	struct stat		stats;

	if (lstat(file->path, &stats))
		return ;
	file->rights = get_rights(stats);
	file->links = stats.st_nlink;
	file->username = (getpwuid(stats.st_uid))->pw_name;
	file->groupname = (getgrgid(stats.st_gid))->gr_name;
	file->bytes = stats.st_size;
	file->date = get_date(stats);
}

void			print_long(t_file file, int colors)
{
	get_info(&file);
	if (colors)
	{
		ft_printf("%s %d %s %s %d %s %s%s\e[m %s\n", file.rights, file.links,
			file.username, file.groupname, file.bytes, file.date, "\e[1;35m",
			file.name, file.path);
	}
	else
	{
		ft_printf("%s %d %s %s %d %s %s %s\n", file.rights, file.links,
			file.username, file.groupname, file.bytes, file.date, file.name,
			file.path);
	}
}
