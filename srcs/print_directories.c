/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_directories.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 18:14:19 by rreedy            #+#    #+#             */
/*   Updated: 2019/04/17 17:19:18 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "options.h"
#include "file.h"
#include "entry.h"
#include "ft_str.h"
#include "ft_printf.h"
#include "ft_mem.h"
#include "ft_put.h"
#include "ft_binarytree.h"
#include <dirent.h>
#include <errno.h>
#include <string.h>

static void		print_error(char *path)
{
	if (ft_strrchr(path, '/'))
	{
		ft_printfd(2,
			"ft_ls: %s: %s\n", ft_strrchr(path, '/') + 1, strerror(errno));
	}
	else
	{
		ft_printfd(2,
			"ft_ls: %s: %s\n", path, strerror(errno));
	}
}

static char		*get_file_path(t_entry *entry, char *file_name)
{
	char	*new_path;
	int		file_name_len;

	file_name_len = ft_strlen(file_name);
	if (entry->path_len == 1 && *(entry->path) == '/')
	{
		new_path = ft_strnew(entry->path_len + file_name_len);
		*new_path = '/';
		ft_strncpy(new_path + entry->path_len, file_name, file_name_len);
	}
	else
	{
		new_path = ft_strnew(entry->path_len + 1 + file_name_len);
		ft_strncpy(new_path, entry->path, entry->path_len);
		new_path[entry->path_len] = '/';
		ft_strncpy(new_path + entry->path_len + 1, file_name, file_name_len);
	}
	return (new_path);
}

static void		get_file(t_binarytree **dirs, char *file_name, t_options ops)
{
	t_file	*file;
	char	*file_path;

	file_path = get_file_path(T_ENTRY(*dirs), file_name);
	file = handle_file(T_ENTRY(*dirs), file_name, file_path, ops);
	if ((ops.flags & OP_BIGR) && file && file->rights && *(file->rights) == 'd'
			&& !ft_strequ(file->name, ".") && !ft_strequ(file->name, ".."))
	{
		insert_entry(&(*dirs)->right, init_entry(ft_strdup(file_path),
				file->sec, file->nsec), ops.compare);
	}
	ft_strdel(&file_path);
}

static void		get_files(t_binarytree **dirs, t_options ops)
{
	struct dirent	*dirent;
	DIR				*dirp;

	dirp = opendir(T_ENTRY(*dirs)->path);
	if (dirp)
	{
		while ((dirent = readdir(dirp)) != 0)
		{
			if (!(ops.flags & OP_A) && dirent->d_name[0] == '.')
				continue;
			get_file(dirs, dirent->d_name, ops);
		}
		(void)closedir(dirp);
	}
	else
		T_ENTRY(*dirs)->bad_access = 1;
}

void			print_dirs(t_binarytree **dirs, int nargs, t_options ops,
					int *newline)
{
	if (*dirs && (*dirs)->left)
		print_dirs(&(*dirs)->left, nargs, ops, newline);
	get_files(dirs, ops);
	if (*newline)
		ft_putchar('\n');
	else
		*newline = 1;
	if (nargs > 1)
		ft_printf("%s:\n", T_ENTRY(*dirs)->path);
	else
		nargs = 2;
	if (T_ENTRY(*dirs)->bad_access)
		print_error(T_ENTRY(*dirs)->path);
	else if (T_ENTRY(*dirs)->files)
	{
		if ((ops.flags & OP_L))
			ft_printf("total %d\n", T_ENTRY(*dirs)->total_blocks);
		print_files(T_ENTRY(*dirs)->files, T_ENTRY(*dirs), ops.print);
	}
	ft_treedel(&(T_ENTRY(*dirs)->files), delete_file);
	if (*dirs && (*dirs)->right)
		print_dirs(&(*dirs)->right, nargs, ops, newline);
	delete_entry((*dirs)->content, 0);
	ft_memdel((void **)dirs);
}
