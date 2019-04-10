/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 18:44:23 by rreedy            #+#    #+#             */
/*   Updated: 2019/04/09 18:47:53 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

/*
# include <dirent.h>
# include <sys/stat.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
*/

typedef struct s_file			t_file;
typedef struct s_entry			t_entry;
typedef struct s_options		t_options;
typedef struct s_binarytree		t_binarytree;

void					print_dirs(t_binarytree **dirs, int nargs,
								t_options options, int *newline);
t_file					*handle_file(t_entry *entry, char *file_name,
								char *file_path, t_options ops);

#endif
