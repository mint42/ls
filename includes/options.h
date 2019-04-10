/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 16:45:59 by rreedy            #+#    #+#             */
/*   Updated: 2019/04/09 16:47:34 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIONS_H
# define OPTIONS_H

# define ALL_OPTIONS "RTafglrt1"
# define MAX_OPS (9)
# define OP_NONE (0x0)
# define OP_1 (0x1)
# define OP_T (0x2)
# define OP_R (0x4)
# define OP_L (0x8)
# define OP_G (0x10)
# define OP_F (0x20)
# define OP_A (0x40)
# define OP_BIGT (0x80)
# define OP_BIGR (0x100)

typedef struct		s_options
{
	int				flags;
	int				(*compare)();
	void			(*print)();
}					t_options;

void				get_options(t_options *ops, char ***argv);

#endif
