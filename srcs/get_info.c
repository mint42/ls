/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 19:08:43 by rreedy            #+#    #+#             */
/*   Updated: 2019/02/07 17:59:22 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char		get_file_type(int mode)
{
	char	type;

	type = 0;
	if (S_ISREG(mode))
		type = '-';
	else if (S_ISBLK(mode))
		type = 'b';
	else if (S_ISCHR(mode))
		type = 'c';
	else if (S_ISDIR(mode))
		type = 'd';
	else if (S_ISLNK(mode))
		type = 'l';
	else if (S_ISFIFO(mode))
		type = 'p';
	else if (S_ISSOCK(mode))
		type = 's';
	return (type);
	
}

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
	rights[0] = get_file_type(stats.st_mode);
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

void			get_info(t_dir *dir, t_file *file, char *path)
{
	struct stat		stats;

	if (lstat(path, &stats))
		return ;
	file->rights = get_rights(stats);
	file->links = stats.st_nlink;
	file->links_len = ft_numlen(file->links);
	file->username = ft_strdup((getpwuid(stats.st_uid))->pw_name);
	file->username_len = ft_strlen(file->username);
	file->groupname = ft_strdup((getgrgid(stats.st_gid))->gr_name);
	file->groupname_len = ft_strlen(file->groupname);
	file->bytes = stats.st_size;
	file->bytes_len = ft_numlen(file->bytes);
	file->date = get_date(stats);
	if (!dir)
		return ;
	if (dir->username_len < file->username_len)
		dir->username_len = file->username_len;
	if (dir->groupname_len < file->groupname_len)
		dir->groupname_len = file->groupname_len;
	if (dir->links_len < file->links_len)
		dir->links_len = file->links_len;
	if (dir->bytes_len < file->bytes_len)
		dir->bytes_len = file->bytes_len;
}
