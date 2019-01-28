/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 00:25:03 by rreedy            #+#    #+#             */
/*   Updated: 2019/01/28 10:59:44 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "ft_ls.h"

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

void		print_illegal_option(char c)
{
	ft_printf("ls: illegal option -- %c\nusage: ls [-%s] [file ...]\n",
			c, ALL_FLAGS);
}
void		print_bad_dirents(char *s)
{
	ft_printf("ls: %s no such file or directory\n", s);
}

void		print_default(char *s)
{
	ft_printf("%s\n", dirent);
}

void		print_rows_and_columns()
{
	static int	terminal_length;
	static int	terminal_width;
	
	if (flags & G)
	{
		if ()
			ft_printf("%-*s", padding, t_file->name);
		else
			ft_printf("%s\n", t_file->name);
	}
	else
	{
		if ()
			ft_printf("%-*s", padding, t_file->name);
		else
			ft_printf("%s\n", t_file->name);
	}
}

void		print_long_colors()
{
	ft_printf("%s %d %s %s %d %s %s\n", file.rights, file.links, file.username,
		file.groupname, file.bytes, file.date, file.name);
}

void		print_long()
{
	ft_printf("%s %d %s %s %d %s %s\n", file.rights, file.links, file.username,
		file.groupname, file.bytes, file.date, file.name);
}

void			print_file(int flags)
{
	int		i;
	
	static void (*print_table)() = 
	{
		print_bad_dirents,
		print_default,
		print_rows_and_columns,
		print_long,
		print_normal_colors,
		print_rows_and_columns_colors,
		print_long_colors,
	};

	print_table[i]();
}
