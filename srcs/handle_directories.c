/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_directories.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 18:18:59 by rreedy            #+#    #+#             */
/*   Updated: 2019/02/19 17:34:53 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		print_error(char *path)
{
	ft_printf("ft_ls: %s: %s\n", ft_strrchr(path, '/') + 1, strerror(errno));
}

static char		*get_file_path(char *dir_path, char *file_name)
{
	char	*new_path;
	int		dir_path_len;
	int		file_name_len;

	dir_path_len = ft_strlen(dir_path);
	file_name_len = ft_strlen(file_name);
	new_path = ft_strnew(dir_path_len + 1 + file_name_len);
	ft_strncpy(new_path, dir_path, dir_path_len);
	new_path[dir_path_len] = '/';
	ft_strncpy(new_path + dir_path_len + 1, file_name, file_name_len);
	return (new_path);
}

static void		get_file(t_binarytree **dirs, char *file_name, t_options ops)
{
	t_file	*file;
	char	*file_path;

	file_path = get_file_path(T_ENTRY(*dirs)->path, file_name);
	file = handle_file(T_ENTRY(*dirs), file_name, file_path, ops.compare);
	if ((ops.flags & OP_BIGR) && file && file->rights && *(file->rights) == 'd'
			&& !ft_strequ(file->name, ".") && !ft_strequ(file->name, ".."))
		insert_entry(&(*dirs)->right,
			init_entry(ft_strdup(file_path)), ops.compare);
	ft_strdel(&file_path);
}

static void		get_files(t_binarytree **dirs, t_options ops)
{
	t_file			*bad_entry;
	struct dirent	*dirent;
	DIR				*dirp;

	bad_entry = 0;
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
	{
		bad_entry = init_file();
		bad_entry->bad_access = 1;
		insert_file(&(T_ENTRY(*dirs)->files), bad_entry, ops.compare);
	}
}

void			print_dirs(t_binarytree **dirs, int nargs, t_options ops,
					int newline)
{
	if (*dirs && (*dirs)->left)
		print_dirs(&(*dirs)->left, nargs, ops, newline);
	get_files(dirs, ops);
	if (newline)
		ft_putchar('\n');
	else
		newline = 1;
	if (nargs > 1)
		ft_printf("%s:\n", T_ENTRY(*dirs)->path);
	else
		nargs = 2;
	if (T_ENTRY(*dirs)->files && T_FILE_D(*dirs)->bad_access)
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
	delete_entry((t_entry **)&(*dirs)->content);
	ft_memdel((void **)dirs);
}
