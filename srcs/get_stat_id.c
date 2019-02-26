/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_stats_id.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:50:21 by rreedy            #+#    #+#             */
/*   Updated: 2019/02/25 17:02:03 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		get_id(t_file *file, struct stat stats)
{
	struct passwd	*user;
	struct group	*group;

	user = getpwuid(stats.st_uid);
	group = getgrgid(stats.st_gid);
	if (user)
		file->username = ft_strdup((getpwuid(stats.st_uid))->pw_name);
	else
		file->username = ft_uitoabase(stats.st_uid, 10);
	file->username_len = ft_strlen(file->username);
	if (group)
		file->groupname = ft_strdup((getgrgid(stats.st_gid))->gr_name);
	else
		file->groupname = ft_uitoabase(stats.st_gid, 10);
	file->groupname_len = ft_strlen(file->groupname);
}
