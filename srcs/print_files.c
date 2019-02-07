/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_default.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 16:20:12 by rreedy            #+#    #+#             */
/*   Updated: 2019/02/06 15:31:08 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_default_colors(t_binarytree *node)
{
	t_file		file;

	file = *T_FILE(node);
	ft_printf("%s%s\e[m\n", "\e[1;35m", file.name);
}

void	print_default(t_binarytree *node)
{
	t_file		file;

	file = *T_FILE(node);
	ft_printf("%s\n", file.name);
}

void		print_long_colors(t_binarytree *node)
{
	t_file		file;

	file = *T_FILE(node);
	ft_printf("%s %d %s %s %d %s %s%s\e[m %s\n", file.rights, file.links,
		file.username, file.groupname, file.bytes, file.date, "\e[1;35m",
		file.name, file.path);
}

void		print_long(t_binarytree *node)
{
	t_file		file;

	file = *T_FILE(node);
	ft_printf("%s %d %s %s %d %s %s %s\n", file.rights, file.links,
		file.username, file.groupname, file.bytes, file.date, file.name,
		file.path);
}
