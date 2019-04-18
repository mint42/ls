/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:55:58 by rreedy            #+#    #+#             */
/*   Updated: 2019/04/17 01:30:12 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"
#include "entry.h"
#include "compare.h"
#include "ft_mem.h"
#include "ft_str.h"
#include "ft_binarytree.h"

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
		*files = ft_treeinit(content, 0);
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

void	delete_file(void *content, size_t content_size)
{
	(void)content_size;
	if (content)
	{
		ft_strdel(&((t_file *)(content))->path);
		ft_strdel(&((t_file *)(content))->name);
		ft_strdel(&((t_file *)(content))->rights);
		ft_strdel(&((t_file *)(content))->username);
		ft_strdel(&((t_file *)(content))->groupname);
		ft_strdel(&((t_file *)(content))->date);
		ft_memdel((void **)&content);
	}
}
