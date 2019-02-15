/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arguments.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 14:15:54 by rreedy            #+#    #+#             */
/*   Updated: 2019/02/12 17:48:33 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	function name:
**		get_arguments
**
**	purpose:
**		loop through the rest of argv and fill the binary trees from the
**		commandline struct (directories, files, and bad_dirents) with their
**		respective dirents
**
**	variables:
**		argv				->	list of arguments sent to main from command line
**		commandline.	->	pointer to a struct to hold the arguments grabbed
**							from the command line (argv)
**		  .options		->	pointer to a bit encoded int to hold options from
**							the command line. encoding: [a g l r R t x y]
**		  .dirs			->	binary tree of compare-sorted directories
**		  .files		->	binary tree of compare-sorted dirents (gets created
**							and deleted multiple times for each directory)
**		  .bad_args		->	binary tree of alphebetically-sorted dirents from 
**							the command line that either don't exist or don't
**							hargve read permissions
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

static void		fill_trees(t_arguments *args, char **argv, int (*compare)())
{
	struct stat		stats;

	if (!(*argv))
	{
		insert_dir(&(args->dirs), init_dir(ft_strdup(".")), compare);
		return (args);
	}
	while (*argv)
	{
		if (stat(*argv, &stats) == 0)
		{
			if (S_ISDIR(stats.st_mode))
				insert_dir(&(args->dirs), init_dir(ft_strdup(*argv)), compare);
			else
				insert_file(&args->files, ft_strdup(*argv), ft_strdup(*argv)),
					compare);
		}
		else
			insert_bad_arg(&(args->bad_args),
					init_bad_arg(ft_strdup(*argv)), compare);
		++argv;
	}
}

t_arguments		get_arguments(char **argv, t_dir files_max, int (*compare)())
{
	t_arguments		args;

	args.dirs = 0;
	args.files = 0;
	args.bad_args = 0;
	fill_trees(&args, argv, compare);
	return (args);
}
