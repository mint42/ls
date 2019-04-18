/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 16:50:24 by rreedy            #+#    #+#             */
/*   Updated: 2019/04/16 01:53:46 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTRY_H
# define ENTRY_H

# include <stddef.h>

# define T_ENTRY(binarytree) ((t_entry *)((binarytree)->content))

typedef struct s_entry			t_entry;
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
