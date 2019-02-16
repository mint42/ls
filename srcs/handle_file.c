/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 16:54:13 by rreedy            #+#    #+#             */
/*   Updated: 2019/02/15 17:48:05 by rreedy           ###   ########.fr       */
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
	if (S_ISREG(stats.st_mode))
		return (rights);
	else if (S_ISBLK(stats.st_mode))
		rights[0] = 'b';
	else if (S_ISCHR(stats.st_mode))
		rights[0] = 'c';
	else if (S_ISDIR(stats.st_mode))
		rights[0] = 'd';
	else if (S_ISLNK(stats.st_mode))
		rights[0] = 'l';
	else if (S_ISFIFO(stats.st_mode))
		rights[0] = 'p';
	else if (S_ISSOCK(stats.st_mode))
		rights[0] = 's';
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

static void		get_stats(t_file *file, t_entry *entry, char *file_path)
{
	struct stat		stats;

	if (lstat(file_path, &stats))
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
	file->time = stats.st_mtime;
	file->bad_access = 0;
	if (entry->max_username_len < file->username_len)
		entry->max_username_len = file->username_len;
	if (entry->max_groupname_len < file->groupname_len)
		entry->max_groupname_len = file->groupname_len;
	if (entry->max_links_len < file->links_len)
		entry->max_links_len = file->links_len;
	if (entry->max_bytes_len < file->bytes_len)
		entry->max_bytes_len = file->bytes_len;
	entry->total_blocks = entry->total_blocks + stats.st_blocks;
}

void			handle_file(t_entry *entry, char *file_name, char *file_path,
					int (*compare)())
{ 
	t_file		*file;

	file = init_file(ft_strdup(file_name));
	get_stats(file, entry, file_path);
	insert_file(&((entry)->files), file, compare);
}
