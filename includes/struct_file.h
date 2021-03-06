/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_file.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 15:38:10 by rreedy            #+#    #+#             */
/*   Updated: 2019/11/27 15:48:37 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_FILE_H
# define STRUCT_FILE_H

# include <stddef.h>

# define T_FILE_F(binarytree) ((t_file *)((binarytree)->content))
# define T_FILE_E(entry) ((t_file *)((entry)->files->content))
# define T_FILE_D(binarytree) T_FILE_E(T_ENTRY(binarytree))

typedef struct s_binarytree		t_binarytree;
typedef struct s_entry			t_entry;

typedef struct			s_file
{
	char				*name;
	unsigned long int	sec;
	unsigned long int	nsec;
	char				*path;
	char				*rights;
	char				*username;
	char				*groupname;
	char				*date;
	int					major;
	int					minor;
	unsigned int		links;
	unsigned int		blocks;
	unsigned long int	bytes;
	size_t				username_len;
	size_t				groupname_len;
	size_t				links_len;
	size_t				bytes_len;
	size_t				major_len;
	size_t				minor_len;
}						t_file;

t_file					*init_file(char *name, char *path);
void					insert_file(t_binarytree **files,
								t_file *content, int (*compare)());
void					print_files(t_binarytree *files, t_entry *entry,
								void (*print)());
void					delete_file(void *content, size_t content_size);

#endif
