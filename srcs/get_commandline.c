/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commandline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 14:31:38 by rreedy            #+#    #+#             */
/*   Updated: 2019/02/07 12:15:04 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

void	set_options(char ***argv, int *ops)
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

void	set_arguments(char **argv, t_commandline *args, int (*compare)())
{
	struct stat		stats;

	if (!(*argv))
	{
		insert_dir(&(args->dirs), init_dir(ft_strdup(".")), compare);
		ft_printf("name: %s\n", ((t_dir *)((args->dirs)->content))->name);
		return ;
	}
	while (*argv)
	{
		if (stat(*argv, &stats) == 0)
		{
			if (S_ISDIR(stats.st_mode))
				insert_dir(&(args->dirs), init_dir(ft_strdup(*argv)), compare);
			else
				insert_file(&(args->files),
					init_file(ft_strdup(*argv), ft_strdup(*argv), 0), compare);
		}
		else
			insert_bad_arg(&(args->bad_args),
					init_bad_arg(ft_strdup(*argv)), compare);
		++argv;
	}
}
