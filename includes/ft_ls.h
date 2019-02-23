/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 18:44:23 by rreedy            #+#    #+#             */
/*   Updated: 2019/02/22 17:56:42 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <sys/stat.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include "libft.h"
# include "config.h"

# define SECONDS_IN_6_MONTHS (15778476)
# define OP_NULL (0x0)
# define OP_Y (0x1)
# define OP_X (0x2)
# define OP_T (0x4)
# define OP_BIGR (0x8)
# define OP_R (0x10)
# define OP_RT (0x14)
# define OP_L (0x20)
# define OP_G (0x40)
# define OP_GL (0x60)
# define OP_A (0x80)
# define OP_1 (0x100)
# define OP_PRINT (0x63)
# define OP_COMPARE (0x14)
# define ALL_OPTIONS "1aglrRtxy"
# define T_ENTRY(binarytree) ((t_entry *)((binarytree)->content))
# define T_BAD_ARG(binarytree) ((t_bad_arg *)((binarytree)->content))
# define T_FILE_F(binarytree) ((t_file *)((binarytree)->content))
# define T_FILE_E(entry) ((t_file *)((entry)->files->content))
# define T_FILE_D(binarytree) T_FILE_E(T_ENTRY(binarytree))

typedef struct			s_file
{
	char				*name;
	unsigned long int	sec;
	unsigned long int	nsec;
	char				*path;
	char				*rights;
	char				*username;
	unsigned int		username_len;
	char				*groupname;
	unsigned int		groupname_len;
	char				*date;
	time_t				time;
	unsigned int		links;
	unsigned int		links_len;
	unsigned long int	bytes;
	unsigned int		bytes_len;
	unsigned int		blocks;
	unsigned int		bad_access;
	char				*color;
}						t_file;

typedef struct			s_entry
{
	char				*path;
	unsigned long int	sec;
	unsigned long int	nsec;
	unsigned int		max_username_len;
	unsigned int		max_groupname_len;
	unsigned int		max_links_len;
	unsigned int		max_bytes_len;
	unsigned int		total_blocks;
	t_binarytree		*files;
}						t_entry;

typedef struct			s_bad_arg
{
	char				*path;
	char				*error_message;
}						t_bad_arg;

typedef struct			s_arguments
{
	t_binarytree		*dirs;
	int					nargs;
	t_entry				*files;
	t_binarytree		*bad_args;
}						t_arguments;

typedef struct			s_options
{
	int					flags;
	int					(*compare)();
	void				(*print)();
}						t_options;

typedef struct			s_cmp
{
	char				*cmp_string;
	unsigned long int	cmp_sec;
	unsigned long int	cmp_nsec;
}						t_cmp;

/*
**	get_options.c and get_arguments.c
*/

void					get_options(t_options *ops, char ***argv);
void					get_arguments(t_arguments *args, char **argv,
							int (*compare)());

/*
**	get_stats.c
*/

t_file					*handle_file(t_entry *entry, char *file_name,
							char *file_path, int (*compare)());

/*
**	print_directories.c
*/

void					print_dirs(t_binarytree **dirs, int nargs,
							t_options options, int newline);

/*
**	files.c, entries.c, and bad_args.c
*/

t_file					*init_file(void);
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
**	comparing_functions.c and printing_functions.c
*/

int						compare_default(t_cmp *cmp1, t_cmp *cmp2);
int						compare_reverse(t_cmp *cmp1, t_cmp *cmp2);
int						compare_time(t_cmp *cmp1, t_cmp *cmp2);
int						compare_time_reverse(t_cmp *cmp1, t_cmp *cmp2);

void					print_default(t_file *file, t_entry *entry);
void					print_default_colors(t_file *file, t_entry *entry);
void					print_long(t_file *file, t_entry *entry);
void					print_long_colors(t_file *file, t_entry *entry);

/*
**	colors.c
*/

char					*get_color(t_file *file);

#endif
