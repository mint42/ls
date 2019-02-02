/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 15:18:15 by rreedy            #+#    #+#             */
/*   Updated: 2019/02/01 19:20:05 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file	init_file(char *name, char *path)
{
	t_file	file;

	file.name = ft_strdup(name);
	file.path = path;
	file.rights = 0;
	file.username = 0;
	file.groupname = 0;
	file.date = 0;
	file.links = 0;
	file.bytes = 0;
	return (file);
}

void	insert_file(t_binarytree **file, t_file content,
				int (*compare)(char *s1, char *s2))
{
	if (!*file)
		*file = ft_treenew(&content);
	else
	{
		if (compare(T_FILE(*file)->name, content.name) >= 0)
			insert_file(&(*file)->right, content, compare);
		else
			insert_file(&(*file)->left, content, compare);
	}
}

void		delete_file(t_file *file)
{
	ft_strdel(&(file->name));
	ft_strdel(&(file->path));
}
