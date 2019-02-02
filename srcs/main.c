/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 10:53:25 by rreedy            #+#    #+#             */
/*   Updated: 2019/02/01 18:48:33 by rreedy           ###   ########.fr       */
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

int			print_bad_option(char c)
{
	ft_printf("ls: illegal option -- %c\nusage: ls [-%s] [file ...]\n",
			c, ALL_OPTIONS);
	return (-1);
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

int			main(int argc, char **argv)
{
	t_commandline	commandline;
	void			(*print)();
	int				(*compare)();

	(void)argc;
	commandline.options = 0;
	commandline.dirs = 0;
	commandline.files = 0;
	commandline.bad_args = 0;
	set_options(&argv, &(commandline.options));
	if (commandline.options == -1)
		return (print_bad_option(**argv));
	compare = get_compare_function(commandline.options);
	print = get_print_function(commandline.options);
	set_arguments(argv, &commandline, compare);
	ft_treeiterdel(&(commandline.bad_args), print_bad_arg, delete_bad_arg);
	if (commandline.files)
	{
		ft_treeiterdel(&(commandline.files), print, delete_file);
		ft_printf("\n");
	}
	print_dirs(&(commandline.dirs), commandline.options, compare, print);
	return (0);
}
