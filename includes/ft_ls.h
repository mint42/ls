/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 18:44:23 by rreedy            #+#    #+#             */
/*   Updated: 2019/02/02 19:13:59 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
#define FT_LS_H

#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "ft_printf.h"
#include "libft.h"

#define SECONDS_IN_6_MONTHS (15778476)

#define OP_NULL (0x0)
#define OP_Y (0x1)
#define OP_X (0x2)
#define OP_T (0x4)
#define OP_BIGR (0x8)
#define OP_R (0x10)
#define OP_L (0x20)
#define OP_G (0x40)
#define OP_GL (0x60)
#define OP_A (0x80)
#define OP_PRINT (0x63)
#define OP_COMPARE (0x14)
#define ALL_OPTIONS "aglrRtxy"
#define T_DIR(binarytree) ((t_dir *)((binarytree)->content))
#define T_FILE(binarytree) ((t_file *)((binarytree)->content))
#define T_BAD_ARG(binarytree) ((t_bad_arg *)((binarytree)->content))

typedef int				(*compare)();
typedef void			(*print)();

typedef struct			s_dir
{
	char				*name;
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

typedef struct			s_bad_arg
{
	char				*name;
	char				*error_message;
}						t_bad_arg;

typedef struct			s_commandline
{
	int					options;
	t_binarytree		*dirs;
	t_binarytree		*files;
	t_binarytree		*bad_args;
}						t_commandline;

void					set_options(char ***argv, int *ops);
void					set_arguments(char **argv, t_commandline *args,
							int (*compare)());


print					get_print_function(int ops);
compare					get_compare_function(int ops);


void					print_dirs(t_binarytree **dirs, int ops,
							int (*compare)(), void (*print)());


void					get_info(t_file *file);


t_file					*init_file(char *name, char *path);
void					insert_file(t_binarytree **file,
							t_file *content,
							int (*compare)(char *s1, char *s2));
void					delete_file(t_file *file);


t_dir					*init_dir(char *name);
void					insert_dir(t_binarytree **dir,
							t_dir *content,
							int (*compare)(char *s1, char *s2));
void					delete_dir(t_dir *dir);


t_bad_arg				*init_bad_arg(char *path);
void					insert_bad_arg(t_binarytree **bad_args,
							t_bad_arg *content,
							int (*compare)(char *s1, char *s2));
void					print_bad_arg(t_bad_arg *bad_arg);
void					delete_bad_arg(t_bad_arg *bad_arg);


void					print_default(t_binarytree *node);
void					print_default_colors(t_binarytree *node);
void					print_long(t_binarytree *node);
void					print_long_colors(t_binarytree *node);


int						compare_reverse(char *s1, char *s2);
#endif
