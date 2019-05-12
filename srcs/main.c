/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 10:53:25 by rreedy            #+#    #+#             */
/*   Updated: 2019/05/11 10:09:12 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "options.h"
#include "arguments.h"
#include "file.h"
#include "entry.h"
#include "bad_arg.h"
#include "ft_mem.h"
#include "ft_printf.h"
#include "ft_binarytree.h"
#include <stdbool.h>

/*
**	The print_bad_option() function gets called if the get_options() funtion
**	fails, meaning a bad flag was sent to the ls program through the command
**	line.
*/

static int		print_bad_option(char c)
{
	ft_printfd(2,
		"ft_ls: illegal option -- %c\nusage: ft_ls [-%s] [file ...]\n",
		c, ALL_OPTIONS);
	return (1);
}

/*
**	The main() function controls the ls program. The command line is parsed by
**	the get_options() and get_arguments() functions, returning information
**	about the command line to the t_options and t_arguments structs
**	respectively. The arguments are split into three different binary trees
**	held in the t_arguments struct;
**	one holding non-readable or non-existant files (arguments.bad_args);
**	one holding valid files (arguments.files),
**	one holding directories (arguments.dirs).
**	These binary trees then get recursed left to right and printed to the
**	terminal. 
*/

int				main(int argc, char **argv)
{
	t_arguments		arguments;
	t_options		ops;
	bool			print_newline;

	(void)argc;
	print_newline = false;
	get_options(&ops, &argv);
	if (ops.flags == -1)
		return (print_bad_option(**argv));
	get_arguments(&arguments, argv, ops);
	if (arguments.bad_args)
		ft_treeiterdel(&(arguments.bad_args), print_bad_arg, delete_bad_arg);
	if ((arguments.files)->files)
	{
		print_files((arguments.files)->files, arguments.files, ops.print);
		ft_treedel(&(arguments.files)->files, delete_file);
		if (arguments.dirs)
			ft_printf("\n");
	}
	ft_memdel((void **)&(arguments.files));
	if (arguments.dirs)
		print_dirs(&(arguments.dirs), arguments.nargs, ops, &print_newline);
	return (0);
}
