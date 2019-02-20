/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comparing_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 18:19:46 by rreedy            #+#    #+#             */
/*   Updated: 2019/02/19 18:08:39 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		compare_default(char *path1, char *path2)
{
	while (path1 && path2 && *path1 && *path2 && *path1 == *path2)
	{
		++path1;
		++path2;
	}
	if (*path1 == '/')
		return (-1);
	if (*path2 == '/')
		return (1);
	return ((unsigned char)*path1 - (unsigned char)*path2);
}

int		compare_reverse(char *path1, char *path2)
{
	while (path1 && path2 && *path1 && *path2 && *path1 == *path2)
	{
		++path1;
		++path2;
	}
	if (*path1 == '/')
		return (1);
	if (*path2 == '/')
		return (-1);
	return ((unsigned char)*path2 - (unsigned char)*path1);
}

int		compare_time(char *path1, char *path2)
{
	struct stat		stats;
	time_t			tmptime;
	time_t			diff;

	lstat(path1, &stats);
	tmptime = stats.st_mtime;
	lstat(path2, &stats);
	diff = stats.st_mtime - tmptime;
	return ((diff) ? diff : compare_default(path1, path2));
}

int		compare_time_reverse(char *path1, char *path2)
{
	struct stat		stats;
	time_t			tmptime;
	time_t			diff;

	lstat(path1, &stats);
	tmptime = stats.st_mtime;
	lstat(path2, &stats);
	diff = tmptime - stats.st_mtime;
	return ((diff) ? diff : compare_reverse(path1, path2));
}
