/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_entries.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:55:52 by rreedy            #+#    #+#             */
/*   Updated: 2019/03/05 16:16:40 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_entry		*init_entry(char *path, unsigned long int sec,
				unsigned long int nsec)
{
	t_entry		*entry;

	entry = (t_entry *)ft_memalloc(sizeof(t_entry));
	entry->path = path;
	entry->path_len = (path) ? ft_strlen(path) : 0;
	entry->sec = sec;
	entry->nsec = nsec;
	entry->slashes = ft_count_c(path, '/');
	entry->bad_access = 0;
	entry->files = 0;
	entry->max_username_len = 0;
	entry->max_links_len = 0;
	entry->max_bytes_len = 0;
	entry->max_major_len = 0;
	entry->max_minor_len = 0;
	entry->total_blocks = 0;
	return (entry);
}

void		update_entry(t_file *file, t_entry *entry)
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

void		insert_entry_cl(t_binarytree **dirs, t_entry *content,
				int (*compare)())
{
	if (!*dirs)
		*dirs = ft_treenew(content);
	else
	{
		if ((compare((t_cmp *)content, (t_cmp *)T_ENTRY(*dirs))) >= 0)
			insert_entry_cl(&(*dirs)->right, content, compare);
		else
			insert_entry_cl(&(*dirs)->left, content, compare);
	}
}

void		insert_entry(t_binarytree **dirs, t_entry *content,
				int (*compare)())
{
	if (!*dirs)
		*dirs = ft_treenew(content);
	else
	{
		if (content->slashes > T_ENTRY(*dirs)->slashes)
			insert_entry(&(*dirs)->left, content, compare);
		else
		{
			if ((compare((t_cmp *)content, (t_cmp *)T_ENTRY(*dirs))) >= 0)
				insert_entry(&(*dirs)->right, content, compare);
			else
				insert_entry(&(*dirs)->left, content, compare);
		}
	}
}

void		delete_entry(t_entry **entry)
{
	if (*entry)
	{
		if ((*entry)->path)
			ft_strdel(&((*entry)->path));
		ft_memdel((void **)entry);
	}
}
