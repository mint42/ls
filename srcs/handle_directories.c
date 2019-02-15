/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_directories.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 18:18:59 by rreedy            #+#    #+#             */
/*   Updated: 2019/02/14 16:18:43 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"


static void		print_error(char *path)
{
	ft_printf("ft_ls: %s: %s\n", ft_strrchr(path, '/') + 1, strerror(errno));
}

static char		*get_file_path(char *dir_path, char *file_name)
{
	char 	*new_path;
	int		dir_path_len;
	int		file_name_len;

	dir_path_len = ft_strlen(dir_path);
	file_name_len = ft_strlen(file_name);
	new_path = ft_strnew(dir_path_len + 1 + file_name_len);
	ft_strncpy(new_path, dir_path, len_entry_path);
	new_path[dir_path_len] = '/';
	ft_strncpy(new_path + dir_path_len + 1, file_name, file_name_len);
	return (new_path);
}

static void		get_file(t_binarytree **dirs, char *file_name, t_options ops)
{
	char	*file_path;
	
	file_path = get_file_path(T_ENTRY(*dirs)->path, name);
	handle_file(&T_ENTRY(*dirs), file_name, file_path, ops);
	if ((ops.flags & OP_BIGR) && T_FILE(T_ENTRY(*dirs)->files)->rights &&
			*(T_FILE(T_ENTRY(*dirs)->files)->rights) == 'd')
		insert_entry(&(dirs)->right,
			init_entry(ft_strdup(file_path)), ops.compare);
	ft_strdel(&file_path);
}

static void		get_files(t_binarytree **dirs, t_options ops)
{
	t_file			bad_entry;
	t_stats			stats;
	struct dirent	*dirent;
	DIR				*dirp;

	bad_file = 0;
	dirp = opendir(T_ENTRY(*dirs)->path);
	if (dirp)
	{
		while ((dirent = readdir(dirp)) != 0)
		{
			if (!(ops.flags & OP_A) && dirent->d_name[0] == '.')
				continue;
			get_file(dirs, dirent->d_name, ops, 0);
		}
		(void)closedir(dirp);
	}
	else
	{
		bad_entry = init_file(0, 0);
		bad_entry->bad_access = 1;
		insert_file(&(T_ENTRY(*dirs)->files), bad_entry, ops.compare);
	}
	return (files);
}

void			print_dirs(t_binarytree **dirs, t_options ops)
{
	if (*dirs && (*dirs)->left)
		print_dirs(&(*dirs)->left, ops);
	ft_printf("%s:\n", T_ENTRY(*dirs)->path);
	init_entry(&T_ENTRY(*dirs));
	get_files(dirs, ops);
	if (T_ENTRY(*dirs)->files && T_FILE(T_ENTRY(*dirs)->files)->bad_access)
		print_error(T_ENTRY(*dirs)->path);
	else if (T_ENTRY(*dirs)->files)
		print_files(T_ENTRY(*dirs)->files, ops.print);
	ft_treedel(&(T_ENTRY(*dirs)->files), delete_file);
	if (*dirs && (*dirs)->right)
	{
		ft_putchar('\n');
		print_dirs(&(*dirs)->right, ops);
	}
	ft_treedelone(dirs, delete_entry);
}
