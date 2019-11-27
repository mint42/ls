/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_entry.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 15:38:04 by rreedy            #+#    #+#             */
/*   Updated: 2019/11/27 15:48:13 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_ENTRY_H
# define STRUCT_ENTRY_H

# include <stddef.h>

# define T_ENTRY(binarytree) ((t_entry *)((binarytree)->content))

typedef struct s_binarytree		t_binarytree;

typedef struct			s_entry
{
	char				*path;
	unsigned long int	sec;
	unsigned long int	nsec;
	size_t				path_len;
	size_t				slashes;
	size_t				bad_access;
	size_t				max_username_len;
	size_t				max_groupname_len;
	size_t				max_links_len;
	size_t				max_bytes_len;
	size_t				max_major_len;
	size_t				max_minor_len;
	size_t				total_blocks;
	t_binarytree		*files;
}						t_entry;

t_entry					*init_entry(char *path, unsigned long int sec,
								unsigned long int nsec);
void					insert_entry_cl(t_binarytree **entry,
								t_entry *content, int (*compare)());
void					insert_entry(t_binarytree **entry,
								t_entry *content, int (*compare)());
void					delete_entry(void *content, size_t content_size);

#endif
