/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 18:19:53 by rreedy            #+#    #+#             */
/*   Updated: 2019/02/16 15:39:07 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_default_colors(t_file *file, t_entry *entry)
{
	(void)entry;
	ft_printf("%s%s\e[m\n", "\e[1;35m", file->name);
}

void	print_default(t_file *file, t_entry *entry)
{
	(void)entry;
	ft_printf("%s\n", file->name);
}

void	print_long_colors(t_file *file, t_entry *entry)
{
	ft_printf("%s%*d %-*s%-*s%*d %s %s%s\e[m -> %s\n",
		file->rights,
		entry->max_links_len + 2, file->links,
		entry->max_username_len + 2, file->username,
		entry->max_groupname_len + 2, file->groupname,
		entry->max_bytes_len, file->bytes,
		file->date,
		"\e[1;35m", file->name,
		file->symlink_path);
}

void	print_long(t_file *file, t_entry *entry)
{
	char	symlink[1024];
	int		symlink_len;

	if (file)
	{
		ft_printf("%s%*d %-*s%-*s%*d %s %s",
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
		write(1, "\n", 1);
	}
}
