/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 18:49:09 by rreedy            #+#    #+#             */
/*   Updated: 2019/01/21 02:42:27 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "ft_ls.h"

# define ALL_FLAGS "aglrRtxy"

typedef	struct			s_binarytree
{
	char				*name;
	struct s_binarytree	*left;
	struct s_binarytree	*right;
}						t_binarytree;

char	*get_colors_fmt(t_binarytree file)
{
	if (file->type)
		return ("\e\[1;37m]%s\e\[m]\n");
}

void	recurse_tree(int flags, t_binarytree file)
{
	if (file->left)
		recurse_tree(flags, file->left);
	print_table(flags)(flags, file);
	if (file->right)
		recurse_tree(flags, file->right);
}

int		ls(int flags, char **path)
{
	DIR				*dirp;
	struct	dirent	*dirent;

	(void)flags;
	dirp = (*path) ? opendir(*path) : opendir(".");
	if (!dirp)
	{
		ft_printf("ls: %s: No such file or directory\n", *path);
		return (1);
	}
	while ((dirent = readdir(dirp)))
		ft_printf("%s\n", dirent->d_name);	
	(void)closedir(dirp);
	return (1);
}

char	**get_flags(int *flags, char **argv)
{
	char	*all_flags;
	char	*cur;
	int		i;

	*flags = 0;
	all_flags = ALL_FLAGS;
	while ((*flags != -1) && *(++argv) && ((*argv)[0] == '-'))
	{
		i = 1;
		if (ft_strequ(*argv, "--"))
			return (++argv);
		while ((*flags != -1) && ((*argv)[i]))
		{
			cur = ft_strchr(all_flags, (*argv)[i]);
			*flags = (cur) ? ((*flags & !(*flags & (L | X | Y))) |
					(1 << (7 - (cur - all_flags)))) : -1;
			++i;
		}
	}
	if (*flags == -1)
	{
		ft_printf("ls: illegal option -- %c\n", (*argv)[i - 1]);
		ft_printf("usage: ls [-aglrRtxy] [file ...]\n");
	}
	return (argv);
}

int		main(int argc, char **argv)
{
	int				flags;

	(void)argc;
	argv = get_flags(&flags, argv);
	if (flags == -1)
		return (1);
	return (ls(flags, argv));
}

/*
**	function name:
**		get_flags
**
**	purpose:
**		to fill a bit encoded int (flags) that holds information about
**		which flags came with the ls command
**
**	variables:
**		flags	  ->	pointer to a bit encoded int to hold flags from the ls
**						command. encoding: [a g l r R t x y]
**		argc	  ->	number of arguments sent to main function
**		argv	  ->	"list" of arguments sent to main function
**		all_flags ->	string to hold all valid flag options
**		cur		  ->	cursor placed at the flag character in all_flags
**						cooresponding to the flag taken from argv
**		i		  ->	index to move through flags in the current argument
**
**	return:
**		returns argv at the start of the dirent arguments
**
**	macros:
**		ALL_FLAGS ->	string containing all valid flags for ls
*/
