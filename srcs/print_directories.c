/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_directories.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 14:41:43 by rreedy            #+#    #+#             */
/*   Updated: 2019/02/06 14:27:11 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	function name:
**		print_bad_option
**
**	purpose:
**		prints the illegal option to stderr
**
**	variables:
**		c			-> the bad option grabbed from the command line
**
**	return:
**		returns -1
**
**	macros:
**		ALL_OPTIONS	->	string containing all valid options for ls
*/

static char			*get_path(char *current_path, char *new_dirent)
{
	char 	*new_path;
	int		len_current_path;
	int		len_new_dirent;

	len_current_path = ft_strlen(current_path);
	len_new_dirent = ft_strlen(new_dirent);
	new_path = ft_strnew(len_current_path + 1 + len_new_dirent);
	ft_strncpy(new_path, current_path, len_current_path);
	new_path[len_current_path] = '/';
	ft_strncpy(new_path + len_current_path + 1, new_dirent, len_new_dirent);
	return (new_path);
}

/*
**	function name:
**		print_bad_option
**
**	purpose:
**		prints the illegal option to stderr
**
**	variables:
**		c			-> the bad option grabbed from the command line
**
**	return:
**		returns -1
**
**	macros:
**		ALL_OPTIONS	->	string containing all valid options for ls
*/

static t_binarytree	*get_files(t_binarytree **dirs, int ops, int (*compare)())
{
	t_binarytree	*files;
	t_file			*content;
	struct dirent	*dirent;
	struct stat		stats;
	DIR				*dirp;
	char			*path;

	files = 0;
	content = 0;
	dirp = opendir(T_DIR(*dirs)->name);
	if (!dirp)
		return (0);
	while ((dirent = readdir(dirp)) != 0)
	{
		if (!(ops & OP_A) && dirent->d_name[0] == '.')
			continue;
		path = get_path(T_DIR(*dirs)->name, dirent->d_name);
		content = init_file(ft_strdup(dirent->d_name), ft_strdup(path));
		insert_file(&files, content, compare);
		if ((ops & OP_BIGR) && lstat(path, &stats) == 0 && S_ISDIR(stats.st_mode))
			insert_dir(&(*dirs)->right, init_dir(ft_strdup(path)), compare);
		ft_strdel(&path);
	}
	(void)closedir(dirp);
	return (files);
}

/*
**	function name:
**		print_bad_option
**
**	purpose:
**		prints the illegal option to stderr
**
**	variables:
**		c			-> the bad option grabbed from the command line
**
**	return:
**		returns -1
**
**	macros:
**		ALL_OPTIONS	->	string containing all valid options for ls
*/

void			print_dirs(t_binarytree **dirs, int ops, int (*compare)(),
					void (*print)())
{
	t_binarytree	*files;

	files = 0;
	if (*dirs && (*dirs)->left)
		print_dirs(&(*dirs)->left, ops, compare, print);
	files = get_files(dirs, ops, compare);
	ft_printf("%s:\n", T_DIR(*dirs)->name);
	if (files)
		ft_treeiter(files, print);
	else
		ft_printf("bad\n");
	ft_putchar('\n');
	ft_treedel(&files, delete_file);
	if (*dirs && (*dirs)->right)
		print_dirs(&(*dirs)->right, ops, compare, print);
}
