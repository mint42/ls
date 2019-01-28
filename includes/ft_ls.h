/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 18:44:23 by rreedy            #+#    #+#             */
/*   Updated: 2019/01/28 10:24:30 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <stdlib.h>
#include "ft_printf.h"
#include "libft.h"

# define SECONDS_IN_6_MONTHS (15778476)
# define L (0x20)
# define X (0x2)
# define Y (0x1)
# define ALL_FLAGS "aglrRtxy"

typedef struct			s_binarytree
{
	char				*name;
	struct s_binarytree	*left;
	struct s_binarytree	*right;
}						t_binarytree;

typedef struct			s_dir
{
	char				*path;
	unsigned int		username_len;
	unsigned int		groupname_len;
	unsigned int		links_len;
	unsigned int		bytes_len;
}						t_dir;

typedef struct			s_file
{
	char				*name;
	char				*path;
	char				*rights;
	char				*username;
	char				*groupname;
	char				*date;
	unsigned int		links;
	unsigned long int	bytes;
}						t_file;

typedef struct			s_lsargs
{
	int					flags;
	t_binarytree		*good_dirs;
	t_binarytree		*good_files;
	t_binarytree		*bad_dirents;
}						t_args;

void					get_info(t_file *file, char *path);

void					get_flags(char ***argv, int flags);
void					get_dirents(char **argv, t_lsargs *args, int (*compare)());

#endif
