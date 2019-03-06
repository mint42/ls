/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:55:58 by rreedy            #+#    #+#             */
/*   Updated: 2019/03/05 18:18:51 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file	*init_file(char *name, char *path)
{
	t_file	*file;

	file = (t_file *)ft_memalloc(sizeof(t_file));
	file->path = path;
	file->name = name;
	file->rights = 0;
	file->username = 0;
	file->username_len = 0;
	file->groupname = 0;
	file->groupname_len = 0;
	file->date = 0;
	file->links = 0;
	file->links_len = 0;
	file->bytes = 0;
	file->bytes_len = 0;
	file->major = -1;
	file->major_len = 0;
	file->minor = -1;
	file->minor_len = 0;
	return (file);
}

void	insert_file(t_binarytree **files, t_file *content,
				int (*compare)())
{
	if (!*files)
		*files = ft_treenew(content);
	else
	{
		if (compare((t_cmp *)content, (t_cmp *)T_FILE_F(*files)) >= 0)
			insert_file(&(*files)->right, content, compare);
		else
			insert_file(&(*files)->left, content, compare);
	}
}

void	print_files(t_binarytree *files, t_entry *entry, void (*print)())
{
	if (files->left)
		print_files(files->left, entry, print);
	print(T_FILE_F(files), entry);
	if (files->right)
		print_files(files->right, entry, print);
}

void	delete_file(t_file **file)
{
	if (*file)
	{
		if ((*file)->path)
			ft_strdel(&((*file)->path));
		if ((*file)->name)
			ft_strdel(&((*file)->name));
		if ((*file)->rights)
			ft_strdel(&((*file)->rights));
		if ((*file)->username)
			ft_strdel(&((*file)->username));
		if ((*file)->groupname)
			ft_strdel(&((*file)->groupname));
		if ((*file)->date)
			ft_strdel(&((*file)->date));
		ft_memdel((void **)file);
	}
}
