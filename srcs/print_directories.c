/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_directories.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 18:14:19 by rreedy            #+#    #+#             */
/*   Updated: 2019/11/27 15:41:09 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "struct_options.h"
#include "struct_file.h"
#include "struct_entry.h"
#include "ft_str.h"
#include "ft_printf.h"
#include "ft_mem.h"
#include "ft_put.h"
#include "ft_binarytree.h"
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

/*
**	The print_error() function prints the error message for the directory
**	instead of printing the files. Error message comes from ERRNO.
*/

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

/*
**	The get_file_path() function takes the current file's name and the path
**	to its directory, and creates an absolute path to the file. The if
**	statement exists to make sure the function doesn't add two slashes to the
**	path when the root folder is being recursed.
*/

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

/*
**	The get_file() function takes a file name, and creates an absolute path to
**	it using the current directory path. handle_file() uses the path to call
**	stat() which gets the file information. Once handle_file() returns, the
**	function checks if the dirent is a directory, and also if the right
**	criteria are met to add it into the the directory tree, so that
**	print_dirs() can recurse to it before the getting to other directories.
**	(This is how this ls implementation handles sub-directory recursion.)
*/

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

/*
**	The get_files() function takes the current directory, opens a directory
**	stream on it, and loops through the stream using readdir() to get each
**	dirent. If the dirent is valid, the function calls get_file() to get file
**	information and to insert that dirent into the files tree.
*/

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

/*
**	The print_dirs() function recurses the directory tree left to right
**	while getting information about the files in the currently recursed
**	directory. After get_files() returns with the filled binary tree of files
**	(in the t_entry struct) it prints those files to the terminal using the
**	print_files function or else it prints an error message. While recuring
**	left to right getting file information it also recurses bottom to top and
**	deletes the directory tree.
*/

void			print_dirs(t_binarytree **dirs, int nargs, t_options ops,
					bool *print_newline)
{
	if (*dirs && (*dirs)->left)
		print_dirs(&(*dirs)->left, nargs, ops, print_newline);
	get_files(dirs, ops);
	if (*print_newline == true)
		ft_putchar('\n');
	else
		*print_newline = true;
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
		print_dirs(&(*dirs)->right, nargs, ops, print_newline);
	delete_entry((*dirs)->content, 0);
	ft_memdel((void **)dirs);
}
