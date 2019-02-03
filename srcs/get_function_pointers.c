/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_function_pointers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 15:18:43 by rreedy            #+#    #+#             */
/*   Updated: 2019/02/02 18:42:01 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

print	get_print_function(int ops)
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

compare	get_compare_function(int ops)
{
	int				(*compare)();
	static int		(*compare_table[OP_COMPARE])() = 
	{
		[OP_NULL] = ft_strcmp,
		[OP_R] = compare_reverse,
	//	[OP_T] = compare_time,
	};

	compare = compare_table[ops & OP_COMPARE];
	return (compare);
}
