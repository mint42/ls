/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 18:44:23 by rreedy            #+#    #+#             */
/*   Updated: 2019/03/04 18:31:55 by rreedy           ###   ########.fr       */
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

# define SECONDS_IN_6_MONTHS (15724800)
# define OP_NONE (0x0)
# define OP_1 (0x1)
# define OP_T (0x2)
# define OP_R (0x4)
# define OP_L (0x8)
# define OP_G (0x10)
# define OP_A (0x20)
# define OP_BIGR (0x40)
# define ST_ALL (OP_L)
# define ST_TIME (OP_T)
# define ST_RIGHTS (OP_G | OP_BIGR)
# define ALL_STATS (OP_L | OP_G | OP_BIGR | OP_T)
# define ALL_PRINT (OP_1 | OP_G | OP_L)
# define ALL_COMPARE (OP_T | OP_R)
# define ALL_OPTIONS "Raglrt1"
# define MAX_OPS (7)
# define MAJOR(dev) (dev >> 24)
# define MINOR(dev) (dev & 0xFFFFFF)
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
	size_t				username_len;
	char				*groupname;
	size_t				groupname_len;
	char				*date;
	time_t				time;
	unsigned int		links;
	size_t				links_len;
	unsigned long int	bytes;
	size_t				bytes_len;
	int					major;
	size_t				major_len;
	int					minor;
	size_t				minor_len;
	unsigned int		blocks;
	char				*color;
}						t_file;

typedef struct			s_entry
{
	char				*path;
	unsigned long int	sec;
	unsigned long int	nsec;
	unsigned int		slashes;
	unsigned int		bad_access;
	unsigned int		max_username_len;
	unsigned int		max_groupname_len;
	unsigned int		max_links_len;
	unsigned int		max_bytes_len;
	unsigned int		max_major_len;
	unsigned int		max_minor_len;
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
**	get_commandline_options.c
**	get_command_line_arguments.c
*/

void					get_options(t_options *ops, char ***argv);
void					get_arguments(t_arguments *args, char **argv,
							t_options ops);

/*
**	print_directories.c
*/

void					print_dirs(t_binarytree **dirs, int nargs,
							t_options options, int *newline);

/*
**	handle_file.c
*/

t_file					*handle_file(t_entry *entry, char *file_name,
							char *file_path, t_options ops);

/*
**	get_stat_date.c
**	get_stat_rights.c
**	get_stat_id.c
**	get_stat_size.c
*/

void					get_rights(t_file *file, struct stat stats);
void					get_id(t_file *file, struct stat stats);
void					get_size(t_file *file, struct stat stats);
void					get_date(t_file *file, struct stat stats);

/*
**	struct_files.c
**	struct_entries.c
**	struct_bad_args.c
*/

t_file					*init_file(char *name, char *path);
void					insert_file(t_binarytree **files,
							t_file *content, int (*compare)());
void					print_files(t_binarytree *files, t_entry *entry,
							void (*print)());
void					delete_file(t_file **file);

t_entry					*init_entry(char *path, unsigned long int sec,
							unsigned long int nsec);
void					update_entry(t_file *file, t_entry *entry);
void					insert_entry_cl(t_binarytree **entry,
							t_entry *content, int (*compare)());
void					insert_entry(t_binarytree **entry,
							t_entry *content, int (*compare)());
void					delete_entry(t_entry **entry);

t_bad_arg				*init_bad_arg(char *path);
void					insert_bad_arg(t_binarytree **bad_args,
							t_bad_arg *content, int (*compare)());
void					print_bad_arg(t_binarytree *node);
void					delete_bad_arg(t_bad_arg **bad_arg);

/*
**	functions_for_comparing.c
**	functions_for_printing.c
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
