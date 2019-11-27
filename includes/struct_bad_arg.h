/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_bad_arg.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 15:37:53 by rreedy            #+#    #+#             */
/*   Updated: 2019/11/27 15:38:25 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_BAD_ARG_H
# define STRUCT_BAD_ARG_H

# include <stddef.h>

# define T_BAD_ARG(binarytree) ((t_bad_arg *)((binarytree)->content))

typedef struct s_binarytree		t_binarytree;

typedef struct		s_bad_arg
{
	char			*path;
	char			*error_message;
}					t_bad_arg;

t_bad_arg			*init_bad_arg(char *path);
void				insert_bad_arg(t_binarytree **bad_args,
							t_bad_arg *content, int (*compare)());
void				print_bad_arg(t_binarytree *node);
void				delete_bad_arg(void *content, size_t content_size);

#endif
