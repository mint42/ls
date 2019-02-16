/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 18:44:23 by rreedy            #+#    #+#             */
/*   Updated: 2019/02/15 17:59:58 by rreedy           ###   ########.fr       */
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
#define T_ENTRY(binarytree) ((t_entry *)((binarytree)->content))
#define T_BAD_ARG(binarytree) ((t_bad_arg *)((binarytree)->content))
#define T_FILE_F(binarytree) ((t_file *)((binarytree)->content))
#define T_FILE_E(entry) ((t_file *)((entry)->files->content))
#define T_FILE_D(binarytree) T_FILE_E(T_ENTRY(binarytree))

typedef int				(*compare)();
typedef void			(*print)();

typedef struct			s_file
{
	char				*name;
	char				*rights;
	char				*username;
	unsigned int		username_len;
	char				*groupname;
	unsigned int		groupname_len;
	char				*date;
	time_t				time;
	char				*symlink_path;
	unsigned int		links;
	unsigned int		links_len;
	unsigned long int	bytes;
	unsigned int		bytes_len;
	unsigned int		bad_access;
}						t_file;

typedef struct			s_entry
{
	char				*path;
	unsigned int		max_username_len;
	unsigned int		max_groupname_len;
	unsigned int		max_links_len;
	unsigned int		max_bytes_len;
	unsigned int		total_blocks;
	t_binarytree		*files;
}						t_entry;

typedef struct			s_arguments
{
	t_binarytree		*dirs;
	t_entry				*files;
	t_binarytree		*bad_args;
}						t_arguments;

typedef struct			s_options
{
	int					flags;
	int					(*compare)();
	void				(*print)();
}						t_options;

typedef struct			s_bad_arg
{
	char				*name;
	char				*error_message;
}						t_bad_arg;

/*
**	get_options.c and get_arguments.c
*/
void					get_options(t_options *ops, char ***argv);
void					get_arguments(t_arguments *args, char **argv,
							int (*compare)());

/*
**	handle_file.c
*/
void					handle_file(t_entry *entry, char *file_name,
							char *file_path, int (*compare)());

/*
**	handle_directories.c
*/
void					print_dirs(t_binarytree **dirs, t_options options);

/*
**	files.c, entries.c, and bad_args.c
*/
t_file					*init_file(char *name);
void					insert_file(t_binarytree **files,
							t_file *content, int (*compare)());
void					print_files(t_binarytree *files, t_entry *entry,
							void (*print)());
void					delete_file(t_file **file);

t_entry					*init_entry(char *path);
void					insert_entry(t_binarytree **entry,
							t_entry *content, int (*compare)());
void					delete_entry(t_entry **entry);

t_bad_arg				*fill_bad_arg(char *path);
void					insert_bad_arg(t_binarytree **bad_args,
							t_bad_arg *content, int (*compare)());
void					print_bad_arg(t_binarytree *node);
void					delete_bad_arg(t_bad_arg **bad_arg);

/*
**	compare_functions.c and print_functions.c
*/
int						compare_default(char *f1, char *f2);
int						compare_reverse(char *f1, char *f2);
int						compare_time(char *f1, char *f2);

void					print_default(t_file *file, t_entry *entry);
void					print_default_colors(t_file *file, t_entry *entry);
void					print_long(t_file *file, t_entry *entry);
void					print_long_colors(t_file *file, t_entry *entry);
#endif
