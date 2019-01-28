/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 10:53:25 by rreedy            #+#    #+#             */
/*   Updated: 2019/01/28 10:55:39 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	function name:
**		main
**
**	purpose:
**		controls the flow of the ls program
**
**	variables:
**		argc			->	number of argv arguments
**		argv			->	list of arguments sent to main function
**		args			->	a struct to hold the arguments grabbed from the
**							command line (argv)
**		  .flags		->	pointer to a bit encoded int to hold flags from the
**							ls command. encoding: [a g l r R t x y]
**		  .good_dirs	->	binary tree of compare-sorted existing directories
**		  .good_files	->	binary tree of compare-sorted existing files
**		  .bad_dirents	->	binary tree of alphebetically-sorted non-existent
**							files and directories
**		compare		 ->		funtion pointer for a jump table that holds the
**							different ways to compare for binary tree insertion
**							with flags: -r, -t
**		print		 ->		funtion pointer for a jump table that holds the
**							different ways to print with
**							flags: -l -r -x -y += -g
**
**	return:
**		returns an int depending on error
**
**	macros:
**		N/A
*/

int		main(int argc, char **argv)
{
	t_lsargs		args;
	type			print;
	type			*compare;

	(void)argc;
	args.flags = 0;
	args.good_dirs = 0;
	args.good_files = 0;
	args.bad_dirents = 0;
	get_flags(&argv, &(args.flags));
	if (args.flags == -1)
	{
		ft_printf("ls: illegal option -- %c\nusage: ls [-%s] [file ...]\n", **argv, ALL_FLAGS);
		return (-1);
	}
	get_compare_function(args.flags, &compare);
	get_print_function_pointer(args.flags, &print);
	get_dirents(argv, &args, compare);
	print_dirents(args, compare, print);
	delete_dirents(args);
	return (0);
}
