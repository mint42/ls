/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lsargs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 10:19:19 by rreedy            #+#    #+#             */
/*   Updated: 2019/01/28 10:20:13 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	function name:
**		get_flags
**
**	purpose:
**		loop though argv and fill a bit encoded int (flags) that holds
**		information about which flags came with the ls command
**
**	variables:
**		flags	  ->	pointer to a bit encoded int to hold flags from the ls
**						command. encoding: [a g l r R t x y]
**		argv	  ->	pointer to list of arguments sent to main function
**		all_flags ->	string to hold all valid flag options
**		cur		  ->	cursor pointer placed at the flag character in all_flags
**						cooresponding to the flag character from argv
**
**	return:
**		N/A
**
**	macros:
**		ALL_FLAGS ->	string containing all valid flags for ls
*/

void	get_flags(char ***argv, int flags)
{
	char	*all_flags;
	char	*cur;

	all_flags = ALL_FLAGS;
	while ((flags != -1) && ++(*argv) && (**argv) && ((***argv) == '-'))
	{
		if (ft_strequ(**argv, "--"))
		{
			++(*argv);
			break ;
		}
		while ((flags != -1) && ++(**argv) && (***argv))
		{
			cur = ft_strchr(all_flags, ***argv);
			flags = (cur) ? ((flags & !(flags & (L | X | Y))) |
					(1 << (7 - (cur - all_flags)))) : -1;
		}
	}
}

/*
**	function name:
**		get_dirents
**
**	purpose:
**		loop through the rest of argv and sort+fill the binary trees from the
**		lsargs struct with the respective dirents
**
**	variables:
**		argv			->	list of arguments sent to main function
**		args			->	pointer to a struct to hold the arguments grabbed
**							from the command line (argv)
**		  .flags		->	pointer to a bit encoded int to hold flags from the
**							ls command. encoding: [a g l r R t x y]
**		  .good_dirs	->	binary tree of compare-sorted existing directories
**		  .good_files	->	binary tree of compare-sorted existing files
**		  .bad_dirents	->	binary tree of alphebetically-sorted non-existent
**							files and directories
**		compare			->	funtion pointer for a jump table that holds the
**							different ways to compare for binary tree insertion
**							with flags: -r, -t
**		stats			->	a stat struct to store stats on a dirent
**
**	return:
**		N/A
**
**	macros:
**		N/A
*/

void	get_dirents(char **argv, t_lsargs *args, int (*compare)())
{
	struct stat		stats;

	if (!(*argv))
		insert(&(args.good_dirs), ".", compare);
	else
		while (*argv)
		{
			if (stat(*folders, &stats) == 0)
			{
				if (S_ISDIR(stats.st_mode))
					insert(&(args.good_dirs), *argv, compare);
				else
					insert(&(args.good_files), *argv, compare);
			}
			else
				insert(&(args.bad_dirents), *argv, compare);
			++argv;
		}
}
