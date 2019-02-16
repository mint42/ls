/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entries.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 14:57:36 by rreedy            #+#    #+#             */
/*   Updated: 2019/02/15 17:24:23 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_entry		*init_entry(char *path)
{
	t_entry		*entry;

	entry = (t_entry *)ft_memalloc(sizeof(t_entry));
	entry->path = path;
	entry->files = 0;
	entry->max_username_len = 0;
	entry->max_links_len = 0;
	entry->max_bytes_len = 0;
	entry->total_blocks = 0;
	return (entry);
}

void		insert_entry(t_binarytree **dirs, t_entry *content,
				int (*compare)(char *s1, char *s2))
{
	if (!*dirs)
		*dirs = ft_treenew(content);
	else
	{
		if ((compare(content->path, T_ENTRY(*dirs)->path)) >= 0)
			insert_entry(&(*dirs)->right, content, compare);
		else
			insert_entry(&(*dirs)->left, content, compare);
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
