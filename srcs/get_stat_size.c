/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_stats_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:50:44 by rreedy            #+#    #+#             */
/*   Updated: 2019/02/25 17:02:49 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		get_size(t_file *file, struct stat stats)
{
	if (file->rights && (file->rights[0] == 'b' || file->rights[0] == 'c'))
	{
		file->major = MAJOR(stats.st_rdev);
		file->major_len = ft_numlen(file->major);
		file->minor = MINOR(stats.st_rdev);
		file->minor_len = ft_numlen(file->minor);
	}
	else
	{
		file->bytes = stats.st_size;
		file->bytes_len = ft_numlen(file->bytes);
	}
}
