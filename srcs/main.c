/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 10:53:25 by rreedy            #+#    #+#             */
/*   Updated: 2019/02/19 18:25:42 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	function name:
**		print_bad_option
**
**	purpose:
**		prints the illegal option to stderr
**
**	variables:
**		c			-> the bad option grabbed from the command line
**
**	return:
**		returns -1
**
**	macros:
**		ALL_OPTIONS	->	string containing all valid options for ls
*/

int		print_bad_option(char c)
{
	ft_printfd(2,
		"ft_ls: illegal option -- %c\nusage: ft_ls [-%s] [file ...]\n",
		c, ALL_OPTIONS);
	return (1);
}

/*
**	function name:
**		main
**
**	purpose:
**		controls the flow of the ls program
**
**	variables:
**		argc			->	number of argv arguments
**		argv			->	list of arguments sent to main from command line
**		commandline.	->	pointer to a struct to hold the arguments grabbed
**							from the command line (argv)
**		  .options		->	pointer to a bit encoded int to hold options from
**							the command line. encoding: [a g l r R t x y]
**		  .dirs			->	binary tree of compare-sorted directories
**		  .files		->	binary tree of compare-sorted dirents (gets created
**							and deleted multiple times for each directory)
**		  .bad_args		->	binary tree of alphebetically-sorted dirents from
**							the command line that either don't exist or don't
**							have read permissions
**		compare			->	funtion pointer for a jump table that holds the
**							different ways to compare for binary tree insertion
**							with flags: -r, -t
**		print			->	funtion pointer for a jump table that holds the
**							different ways to print with
**							flags: -l -r -x -y += -g
**	return:
**		returns an int depending on error
**
**	macros:
**		N/A
*/

int		main(int argc, char **argv)
{
	t_arguments		arguments;
	t_options		ops;

	(void)argc;
	get_options(&ops, &argv);
	if (ops.flags == -1)
		return (print_bad_option(**argv));
	get_arguments(&arguments, argv, ops.compare);
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
		print_dirs(&(arguments.dirs), arguments.nargs, ops, 0);
	return (0);
}
