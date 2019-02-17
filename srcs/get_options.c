/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 13:52:09 by rreedy            #+#    #+#             */
/*   Updated: 2019/02/16 15:22:10 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static print		get_print_function(int ops)
{
	void			(*print)();
	static void		(*print_table[OP_PRINT])() = 
	{
		[OP_NULL] = print_default,
		[OP_G] = print_default_colors,
		[OP_L] = print_long,
		[OP_GL] = print_long_colors,
	//	[OP_X] = print_horizontal,
	//	[OP_Y] = print_vertical,
	};

	print = print_table[ops & OP_PRINT];
	return (print);
}

static compare		get_compare_function(int ops)
{
	int				(*compare)();
	static int		(*compare_table[OP_COMPARE + 1])() = 
	{
		[OP_NULL] = compare_default,
		[OP_R] = compare_reverse,
		[OP_T] = compare_time,
		[OP_RT] = compare_time_reverse,
	};

	compare = compare_table[ops & OP_COMPARE];
	return (compare);
}

/*
**	function name:
**		get_options
**
**	purpose:
**		loop though argv and fill a bit encoded int (flags) that holds
**		information about which flags that came from the command line. also
**		move argv past the flag strings
**
**	variables:
**		options		->	pointer to a bit encoded int to hold flags from the ls
**						command. encoding: [a g l r R t x y]
**		argv	  		->	pointer to list of arguments sent to main function
**		all_options	->	string to hold all valid options
**		cur		  	->	cursor pointer placed at the flag character in all_flags
**						cooresponding to the flag character from argv
**
**	return:
**		N/A
**
**	macros:
**		ALL_OPTIONS	->	string containing all valid options for ls
*/

static void			fill_flags(int *ops, char ***argv)
{
	char	*all_ops;
	char	*cur;

	all_ops = ALL_OPTIONS;
	while ((*ops != -1) && ++(*argv) && (**argv) && ((***argv) == '-'))
	{
		if (ft_strequ(**argv, "--"))
		{
			++(*argv);
			break ;
		}
		while ((*ops != -1) && ++(**argv) && (***argv))
		{
			cur = ft_strchr(all_ops, ***argv);
			if (cur)
				*ops = ((OP_L | OP_X | OP_Y) & (1 << (7 - (cur - all_ops)))) ?
						((*ops & ~(*ops & (OP_L | OP_X | OP_Y))) |
						(1 << (7 - (cur - all_ops)))) :
						((*ops) | (1 << (7 - (cur - all_ops))));
			else
				*ops = -1;
		}
	}
}

void			get_options(t_options *ops, char ***argv)
{
	ops->flags = 0;
	ops->compare = 0;
	ops->print = 0;
	fill_flags(&(ops->flags), argv);
	if (ops->flags == -1)
		return ;
	ops->compare = get_compare_function(ops->flags);
	ops->print = get_print_function(ops->flags);
}
