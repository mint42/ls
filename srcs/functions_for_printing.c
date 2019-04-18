/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 18:19:53 by rreedy            #+#    #+#             */
/*   Updated: 2019/04/15 04:32:13 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"
#include "entry.h"
#include "colors.h"
#include "ft_str.h"
#include "ft_printf.h"
#include "ft_put.h"
#include <unistd.h>

static void		print_size(t_file *file, t_entry *entry)
{
	if (file->major != -1)
	{
		ft_printf("%*u, %*u ",
			entry->max_major_len, file->major,
			entry->max_minor_len, file->minor);
	}
	else if (entry->max_major_len != 0)
	{
		ft_printf("%*lu ", entry->max_major_len + entry->max_minor_len + 2,
			file->bytes);
	}
	else
	{
		ft_printf("%*lu ", entry->max_bytes_len, file->bytes);
	}
}

void			print_long(t_file *file, t_entry *entry)
{
	char	symlink[1024];
	int		symlink_len;

	if (file)
	{
		ft_printf("%s%*u %-*s%-*s",
			file->rights,
			entry->max_links_len + 2, file->links,
			entry->max_username_len + 2, file->username,
			entry->max_groupname_len + 2, file->groupname);
		print_size(file, entry);
		ft_printf("%s %s", file->date, file->name);
		if (*(file->rights) == 'l')
		{
			symlink_len = readlink(file->path, symlink, 1023);
			if (symlink_len != -1)
			{
				symlink[symlink_len] = '\0';
				ft_printf(" -> %s", symlink);
			}
		}
		ft_putchar('\n');
	}
}

void			print_long_colors(t_file *file, t_entry *entry)
{
	char	symlink[1024];
	int		symlink_len;

	if (file)
	{
		ft_printf("%s%*u %-*s%-*s",
			file->rights,
			entry->max_links_len + 2, file->links,
			entry->max_username_len + 2, file->username,
			entry->max_groupname_len + 2, file->groupname);
		print_size(file, entry);
		ft_printf("%s %s%s\e[m", file->date, get_color(file), file->name);
		if (*(file->rights) == 'l')
		{
			symlink_len = readlink(file->path, symlink, 1023);
			if (symlink_len != -1)
			{
				symlink[symlink_len] = '\0';
				ft_printf(" -> %s", symlink);
			}
		}
		ft_putchar('\n');
	}
}

void			print_default(t_file *file, t_entry *entry)
{
	(void)entry;
	ft_printf("%s\n", file->name);
}

void			print_default_colors(t_file *file, t_entry *entry)
{
	(void)entry;
	ft_printf("%s%s\e[m\n", get_color(file), file->name);
}
