/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_stats.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 14:05:21 by rreedy            #+#    #+#             */
/*   Updated: 2019/02/22 17:26:59 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char		*get_rights(t_file *file, struct stat stats)
{
	unsigned int	bits;
	int				i;

	i = 10;
	bits = (stats.st_mode) & (S_IRWXU | S_IRWXG | S_IRWXO);
	file->rights = ft_strdup("-rwxrwxrwx");
	while (--i >= 0)
		if (!((bits >> i) & 1))
			file->rights[9 - i] = '-';
	if (ft_strchr(file->rights, 'x'))
		file->color = COLOR_EXE;
	if (S_ISBLK(stats.st_mode))
		file->rights[0] = 'b';
	else if (S_ISCHR(stats.st_mode))
		file->rights[0] = 'c';
	else if (S_ISDIR(stats.st_mode) && (file->color = COLOR_DIR))
		file->rights[0] = 'd';
	else if (S_ISLNK(stats.st_mode) && (file->color = COLOR_LNK))
		file->rights[0] = 'l';
	else if (S_ISFIFO(stats.st_mode))
		file->rights[0] = 'p';
	else if (S_ISSOCK(stats.st_mode))
		file->rights[0] = 's';
	return (file->rights);
}

static char		*get_date(struct stat stats)
{
	char	*date;

	date = ctime(&stats.st_mtimespec.tv_sec);
	if ((time(NULL) - SECONDS_IN_6_MONTHS) > stats.st_mtime)
		ft_sprintf(&date, "%-8.6s%.4s", date + 4, date + 20);
	else if ((time(NULL) + SECONDS_IN_6_MONTHS) < stats.st_mtime)
		ft_sprintf(&date, "%-8.6s%.4s", date + 4, date + 20);
	else
		ft_sprintf(&date, "%.12s", date + 4);
	return (date);
}

static void		get_stats(t_file *file, char *file_name, char *file_path)
{
	struct stat		stats;

	if (lstat(file_path, &stats))
		return ;
	file->path = ft_strdup(file_path);
	file->name = ft_strdup(file_name);
	file->rights = get_rights(file, stats);
	file->links = stats.st_nlink;
	file->links_len = ft_numlen(file->links);
	file->username = ft_strdup((getpwuid(stats.st_uid))->pw_name);
	file->username_len = ft_strlen(file->username);
	file->groupname = ft_strdup((getgrgid(stats.st_gid))->gr_name);
	file->groupname_len = ft_strlen(file->groupname);
	file->bytes = stats.st_size;
	file->bytes_len = ft_numlen(file->bytes);
	file->date = get_date(stats);
	file->sec = stats.st_mtimespec.tv_sec;
	file->nsec = stats.st_mtimespec.tv_nsec;
	file->blocks = stats.st_blocks;
}

static void		update_entry(t_file *file, t_entry *entry)
{
	if (entry->max_username_len < file->username_len)
		entry->max_username_len = file->username_len;
	if (entry->max_groupname_len < file->groupname_len)
		entry->max_groupname_len = file->groupname_len;
	if (entry->max_links_len < file->links_len)
		entry->max_links_len = file->links_len;
	if (entry->max_bytes_len < file->bytes_len)
		entry->max_bytes_len = file->bytes_len;
	entry->total_blocks = entry->total_blocks + file->blocks;
}

t_file			*handle_file(t_entry *entry, char *file_name, char *file_path,
					int (*compare)())
{
	t_file		*file;

	file = init_file();
	get_stats(file, file_name, file_path);
	update_entry(file, entry);
	insert_file(&((entry)->files), file, compare);
	return (file);
}
