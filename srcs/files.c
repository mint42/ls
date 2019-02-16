/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 15:18:15 by rreedy            #+#    #+#             */
/*   Updated: 2019/02/15 17:59:25 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file	*init_file(char *name)
{
	t_file	*file;

	file = (t_file *)ft_memalloc(sizeof(t_file));
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
	file->bad_access = 0;
	return (file);
}

void	insert_file(t_binarytree **files, t_file *content,
				int (*compare)(char *s1, char *s2))
{
	if (!*files)
		*files = ft_treenew(content);
	else
	{
		if (compare(content->name, T_FILE_F(*files)->name) >= 0)
			insert_file(&(*files)->right, content, compare);
		else
			insert_file(&(*files)->left, content, compare);
	}
}

void		print_files(t_binarytree *files, t_entry *entry, void (*print)())
{
	if (files->left)
		print_files(files->left, entry, print);
	print(T_FILE_F(files), entry);
	if (files->right)
		print_files(files->right, entry, print);
}

void		delete_file(t_file **file)
{
	if (*file)
	{
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
		if ((*file)->symlink_path)
			ft_strdel(&((*file)->symlink_path));
		ft_memdel((void **)file);
	}
}
