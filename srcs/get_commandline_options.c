/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commandline_options.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:47:28 by rreedy            #+#    #+#             */
/*   Updated: 2019/11/27 15:41:09 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_options.h"
#include "struct_cmp.h"
#include "print.h"
#include "ft_str.h"
#include <time.h>

/*
**	The get_print_function() uses a jump table to determine which print
**	function should be used by bitwise and-ing to get the index of the table.
*/

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

/*
**	The get_compare_function() uses a jump table to determine which compare
**	function should be used by bitwise and-ing to get the index of the table.
*/

static void		*get_compare_function(int ops)
{
	int				(*compare)();
	static int		(*compare_table[ALL_COMPARE + 1])() = {
		[OP_NONE] = compare_default,
		[OP_F] = compare_not,
		[OP_R] = compare_reverse,
		[OP_T] = compare_time,
		[OP_R | OP_T] = compare_time_reverse,
	};

	compare = compare_table[ops & ALL_COMPARE];
	return (compare);
}

/*
**	The get_ops() function uses bit math to either toggle the L and 1 flags
**	on or off given the current flag, or else turns on the new flag using
**	a bit shift.
*/

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

/*
**	The fill_flags() function loops through argv and uses bit operators to
**	toggle the respective bits for the current flag.
**	The bit encoding:
**		R T a f g l r t 1
**	-1 being 0x1, -t being 0x2 and so on.
**	Macros for this can be found in the	includes/options.h file
*/

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

/*
**	The get_options() function fills the t_options struct with a bit encoded
**	int	with the flags, and uses those flags to choose function pointers for
**	the comparing and printing functions.
*/

void			get_options(t_options *ops, char ***argv)
{
	ops->flags = OP_1;
	ops->compare = 0;
	ops->print = 0;
	fill_flags(&(ops->flags), argv);
	if (ops->flags == -1)
		return ;
	if (ops->flags & OP_F)
	{
		ops->flags = ops->flags | OP_A;
		if (ops->flags & OP_R)
			ops->flags = ops->flags ^ OP_R;
		if (ops->flags & OP_T)
			ops->flags = ops->flags ^ OP_T;
	}
	ops->compare = get_compare_function(ops->flags);
	ops->print = get_print_function(ops->flags);
}
