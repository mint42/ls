/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 15:18:15 by rreedy            #+#    #+#             */
/*   Updated: 2019/02/02 19:11:51 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file	*init_file(char *name, char *path)
{
	t_file	*file;

	file = (t_file *)ft_memalloc(sizeof(t_file));
	file->name = name;
	file->path = path;
	file->rights = 0;
	file->username = 0;
	file->groupname = 0;
	file->date = 0;
	file->links = 0;
	file->bytes = 0;
	get_info(file);
	return (file);
}

void	insert_file(t_binarytree **file, t_file *content,
				int (*compare)(char *s1, char *s2))
{
	if (!*file)
		*file = ft_treenew(content);
	else
	{
		if ((compare(content->name, T_FILE(*file)->name)) >= 0)
			insert_file(&(*file)->right, content, compare);
		else
			insert_file(&(*file)->left, content, compare);
	}
}

void		delete_file(t_file *file)
{
	if (file)
	{
		ft_strdel(&(file->name));
		ft_strdel(&(file->path));
		if (file->rights)
			ft_strdel(&(file->rights));
		if (file->username)
			ft_strdel(&(file->username));
		if (file->groupname)
			ft_strdel(&(file->groupname));
		if (file->date)
			ft_strdel(&(file->date));
		ft_memdel((void **)&file);
	}
}
