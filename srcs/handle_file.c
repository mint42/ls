/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 16:06:22 by rreedy            #+#    #+#             */
/*   Updated: 2019/03/03 19:07:46 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		get_stats(t_file *file, t_options ops)
{
	struct stat		stats;

	if (lstat(file->path, &stats))
		return (1);
	get_rights(file, stats);
	file->sec = stats.st_mtimespec.tv_sec;
	file->nsec = stats.st_mtimespec.tv_nsec;
	if (ops.flags & OP_L)
	{
		get_size(file, stats);
		get_date(file, stats);
		get_id(file, stats);
		file->links = stats.st_nlink;
		file->links_len = ft_numlen(file->links);
		file->blocks = stats.st_blocks;
	}
	return (0);
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
	if (entry->max_minor_len < file->minor_len)
		entry->max_minor_len = file->minor_len;
	if (entry->max_major_len < file->major_len)
		entry->max_major_len = file->major_len;
	if ((entry->max_major_len || entry->max_minor_len) &&
		entry->max_bytes_len >
			entry->max_major_len + entry->max_minor_len + 2)
	{
		entry->max_major_len = entry->max_major_len + (entry->max_bytes_len -
			(entry->max_major_len + entry->max_minor_len + 2));
	}
	entry->total_blocks = entry->total_blocks + file->blocks;
}

t_file			*handle_file(t_entry *entry, char *file_name, char *file_path,
					t_options ops)
{
	t_file		*file;
	int			error;

	error = 0;
	file = init_file(ft_strdup(file_name), ft_strdup(file_path));
	error = get_stats(file, ops);
	if (error && ((OP_L | OP_T | OP_BIGR | OP_G) & ops.flags))
	{
		delete_file(&file);
		return (0);
	}
	update_entry(file, entry);
	insert_file(&((entry)->files), file, ops.compare);
	return (file);
}
