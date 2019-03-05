/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commandline_options.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:47:28 by rreedy            #+#    #+#             */
/*   Updated: 2019/03/04 16:14:48 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		*get_print_function(int ops)
{
	void			(*print)();
	static void		(*print_table[ALL_PRINT + 1])() = {
		[OP_1] = print_default,
		[OP_L] = print_long,
		[OP_1 | OP_G] = print_default_colors,
		[OP_L | OP_G] = print_long_colors,
	};

	print = print_table[ops & ALL_PRINT];
	return (print);
}

static void		*get_compare_function(int ops)
{
	int				(*compare)();
	static int		(*compare_table[ALL_COMPARE + 1])() = {
		[OP_NONE] = compare_default,
		[OP_R] = compare_reverse,
		[OP_T] = compare_time,
		[OP_R | OP_T] = compare_time_reverse,
	};

	compare = compare_table[ops & ALL_COMPARE];
	return (compare);
}

static int		get_ops(int ops, char *cur, char *all_ops)
{
	if ((OP_1 | OP_L) & (1 << ((MAX_OPS - 1) - (cur - all_ops))))
	{
		ops = (ops & ~(ops & (OP_1 | OP_L))) |
			(1 << ((MAX_OPS - 1) - (cur - all_ops)));
	}
	else
		ops = (ops) | (1 << ((MAX_OPS - 1) - (cur - all_ops)));
	return (ops);
}

static void		fill_flags(int *ops, char ***argv)
{
	char	*all_ops;
	char	*cur;

	all_ops = ALL_OPTIONS;
	while ((*ops != -1) && ++(*argv) && (**argv) && ((***argv) == '-'))
	{
		if (ft_strequ(**argv, "-"))
			break ;
		if (ft_strequ(**argv, "--"))
		{
			++(*argv);
			break ;
		}
		while ((*ops != -1) && ++(**argv) && (***argv))
		{
			cur = ft_strchr(all_ops, ***argv);
			if (cur)
				*ops = get_ops(*ops, cur, all_ops);
			else
				*ops = -1;
		}
	}
}

void			get_options(t_options *ops, char ***argv)
{
	ops->flags = OP_1;
	ops->compare = 0;
	ops->print = 0;
	fill_flags(&(ops->flags), argv);
	if (ops->flags == -1)
		return ;
	ops->compare = get_compare_function(ops->flags);
	ops->print = get_print_function(ops->flags);
}
