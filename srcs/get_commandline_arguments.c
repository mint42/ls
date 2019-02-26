/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commandline_arguments.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:47:07 by rreedy            #+#    #+#             */
/*   Updated: 2019/02/25 16:47:22 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		fill_trees(t_arguments *args, char **argv, t_options ops)
{
	struct stat		stats;

	if (!(*argv))
	{
		insert_entry(&(args->dirs), init_entry(ft_strdup(".")), ops.compare);
		return ;
	}
	while (*argv)
	{
		if (lstat(*argv, &stats) == 0)
		{
			if (S_ISDIR(stats.st_mode))
			{
				insert_entry(&(args->dirs), init_entry(ft_strdup(*argv)),
					ops.compare);
			}
			else
				handle_file(args->files, *argv, *argv, ops);
		}
		else
			insert_bad_arg(&(args->bad_args),
					fill_bad_arg(ft_strdup(*argv)), compare_default);
		++(args->nargs);
		++argv;
	}
}

void			get_arguments(t_arguments *args, char **argv, t_options ops)
{
	args->dirs = 0;
	args->nargs = 0;
	args->files = init_entry(0);
	args->bad_args = 0;
	fill_trees(args, argv, ops);
}
