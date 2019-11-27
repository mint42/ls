/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 16:56:33 by rreedy            #+#    #+#             */
/*   Updated: 2019/11/27 15:41:29 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H

# include "struct_options.h"

# define ALL_PRINT (OP_1 | OP_G | OP_L)

typedef struct s_file	t_file;
typedef struct s_entry	t_entry;

void		print_default(t_file *file, t_entry *entry);
void		print_default_colors(t_file *file, t_entry *entry);
void		print_long(t_file *file, t_entry *entry);
void		print_long_colors(t_file *file, t_entry *entry);

#endif
