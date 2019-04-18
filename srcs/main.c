/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 10:53:25 by rreedy            #+#    #+#             */
/*   Updated: 2019/04/16 01:54:33 by rreedy           ###   ########.fr       */
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

int		print_bad_option(char c)
{
	ft_printfd(2,
		"ft_ls: illegal option -- %c\nusage: ft_ls [-%s] [file ...]\n",
		c, ALL_OPTIONS);
	return (1);
}

int		main(int argc, char **argv)
{
	t_arguments		arguments;
	t_options		ops;
	int				newline;

	newline = 0;
	(void)argc;
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
		print_dirs(&(arguments.dirs), arguments.nargs, ops, &newline);
	return (0);
}
