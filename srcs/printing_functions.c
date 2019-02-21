/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 18:19:53 by rreedy            #+#    #+#             */
/*   Updated: 2019/02/20 17:19:56 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_default_colors(t_file *file, t_entry *entry)
{
	(void)entry;
	ft_printf("%s%s\e[m\n", get_color(file), file->name);
}

void	print_default(t_file *file, t_entry *entry)
{
	(void)entry;
	ft_printf("%s\n", file->name);
}

void	print_long_colors(t_file *file, t_entry *entry)
{
	char	symlink[1024];
	int		symlink_len;

	if (file)
	{
		ft_printf("%s%*u %-*s%-*s%*u %s %s%s\e[m",
				file->rights,
				entry->max_links_len + 2, file->links,
				entry->max_username_len + 2, file->username,
				entry->max_groupname_len + 2, file->groupname,
				entry->max_bytes_len, file->bytes,
				file->date,
				get_color(file),
				file->name);
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

void	print_long(t_file *file, t_entry *entry)
{
	char	symlink[1024];
	int		symlink_len;

	if (file)
	{
		ft_printf("%s%*u %-*s%-*s%*u %s %s",
				file->rights,
				entry->max_links_len + 2, file->links,
				entry->max_username_len + 2, file->username,
				entry->max_groupname_len + 2, file->groupname,
				entry->max_bytes_len, file->bytes,
				file->date,
				file->name);
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
