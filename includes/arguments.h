/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 16:47:39 by rreedy            #+#    #+#             */
/*   Updated: 2019/04/09 17:10:34 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGUMENTS_H
# define ARGUMENTS_H

typedef struct s_options		t_options;
typedef struct s_entry			t_entry;
typedef struct s_binarytree		t_binarytree;

typedef struct		s_arguments
{
	t_binarytree	*dirs;
	int				nargs;
	t_entry			*files;
	t_binarytree	*bad_args;
}					t_arguments;

void				get_arguments(t_arguments *args, char **argv,
							t_options ops);

#endif
