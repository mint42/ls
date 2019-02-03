/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 15:18:23 by rreedy            #+#    #+#             */
/*   Updated: 2019/02/02 19:06:36 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dir	*init_dir(char *name)
{
	t_dir	*dir;

	dir = (t_dir *)ft_memalloc(sizeof(t_dir));
	dir->name = name;
	dir->username_len = 0;
	dir->groupname_len = 0;
	dir->links_len = 0;
	dir->bytes_len = 0;
	return (dir);
}

void		insert_dir(t_binarytree **dirs, t_dir *content,
				int (*compare)(char *s1, char *s2))
{
	if (!*dirs)
		*dirs = ft_treenew(content);
	else
	{
		if ((compare(content->name, T_DIR(*dirs)->name)) >= 0)
			insert_dir(&(*dirs)->right, content, compare);
		else
			insert_dir(&(*dirs)->left, content, compare);
	}
}

void		delete_dir(t_dir *dir)
{
	if (dir)
	{
		ft_strdel(&(dir->name));
		ft_memdel((void **)&dir);
	}
}
