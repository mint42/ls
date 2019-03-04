/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_entries.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:55:52 by rreedy            #+#    #+#             */
/*   Updated: 2019/03/03 20:10:13 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_entry		*init_entry(char *path, unsigned long int sec,
				unsigned long int nsec)
{
	t_entry		*entry;

	entry = (t_entry *)ft_memalloc(sizeof(t_entry));
	entry->path = path;
	entry->sec = sec;
	entry->nsec = nsec;
	entry->files = 0;
	entry->max_username_len = 0;
	entry->max_links_len = 0;
	entry->max_bytes_len = 0;
	entry->max_major_len = 0;
	entry->max_minor_len = 0;
	entry->total_blocks = 0;
	return (entry);
}

void		insert_entry(t_binarytree **dirs, t_entry *content,
				int (*compare)(), int commandline)
{
	if (!*dirs)
		*dirs = ft_treenew(content);
	else
	{
		if (!commandline && (ft_count_c(content->path, '/') >
			ft_count_c(T_ENTRY(*dirs)->path, '/')))
		{
			insert_entry(&(*dirs)->left, content, compare, commandline);
		}
		else
		{
			if ((compare((t_cmp *)content, (t_cmp *)T_ENTRY(*dirs))) >= 0)
				insert_entry(&(*dirs)->right, content, compare, commandline);
			else
				insert_entry(&(*dirs)->left, content, compare, commandline);
		}
	}
}

void		delete_entry(t_entry **entry)
{
	if (entry)
	{
		ft_strdel(&((*entry)->path));
		ft_memdel((void **)entry);
	}
}
