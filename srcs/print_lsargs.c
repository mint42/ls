/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lsargs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 10:20:58 by rreedy            #+#    #+#             */
/*   Updated: 2019/01/28 10:57:27 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	function name:
**		print_dirents
**
**	purpose:
**		loop through the rest of argv and sort+fill the binary trees from the
**		lsargs struct with the respective dirents
**
**	variables:
**		args			->	a struct to hold the arguments grabbed from the
**							command line (argv)
**		  .flags		->	pointer to a bit encoded int to hold flags from the
**							ls command. encoding: [a g l r R t x y]
**		  .good_dirs	->	binary tree of compare-sorted existing directories
**		  .good_files	->	binary tree of compare-sorted existing files
**		  .bad_dirents	->	binary tree of alphebetically-sorted non-existent
**							files and directories
**
**	return:
**		N/A
**
**	macros:
**		N/A
*/

void	print_dirents(t_lsargs args, printfunction)
{
	treeiter(args.bad_dirents, print_bad_dirents);
	treeiter(args.good_files, printfunction);
	recursive_printing(args, printfunction);
}
