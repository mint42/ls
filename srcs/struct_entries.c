/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_entries.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:55:52 by rreedy            #+#    #+#             */
/*   Updated: 2019/04/09 17:42:15 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entry.h"
#include "compare.h"
#include "libft.h"

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
