/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 16:06:22 by rreedy            #+#    #+#             */
/*   Updated: 2019/03/05 19:38:12 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		stats_all(t_file *file, int flags)
{
	struct stat		stats;

	if (lstat(file->path, &stats))
		return (1);
	get_rights(file, stats);
	file->sec = stats.st_mtimespec.tv_sec;
	file->nsec = stats.st_mtimespec.tv_nsec;
	if (flags & OP_L)
	{
		get_size(file, stats);
		get_date(file, stats, flags);
		get_id(file, stats);
		file->links = stats.st_nlink;
		file->links_len = ft_numlen(file->links);
		file->blocks = stats.st_blocks;
	}
	return (0);
}

static int		stats_time(t_file *file)
{
	struct stat		stats;

	if (lstat(file->path, &stats))
		return (1);
	file->sec = stats.st_mtimespec.tv_sec;
	file->nsec = stats.st_mtimespec.tv_nsec;
	return (0);
}

static int		stats_rights(t_file *file)
{
	struct stat		stats;

	if (lstat(file->path, &stats))
		return (1);
	get_rights(file, stats);
	return (0);
}

t_file			*handle_file(t_entry *entry, char *file_name, char *file_path,
					t_options ops)
{
	t_file			*file;
	int				error;

	error = 0;
	file = init_file(ft_strdup(file_name), ft_strdup(file_path));
	if (ops.flags & OP_L)
		error = stats_all(file, ops.flags);
	else if (ops.flags & (OP_G | OP_BIGR))
		error = stats_rights(file);
	else if (ops.flags & OP_T)
		error = stats_time(file);
	if (error)
	{
		delete_file(&file);
		return (0);
	}
	update_entry(file, entry);
	insert_file(&((entry)->files), file, ops.compare);
	return (file);
}
