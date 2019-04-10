/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 16:59:42 by rreedy            #+#    #+#             */
/*   Updated: 2019/04/09 18:54:54 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATS_H
# define STATS_H

# include "options.h"
# include <sys/stat.h>

# define SECONDS_IN_6_MONTHS (15724800)
# define ALL_STATS (OP_L | OP_G | OP_BIGR | OP_T)
# define MAJOR(dev) (dev >> 24)
# define MINOR(dev) (dev & 0xFFFFFF)


typedef struct s_file	t_file;
typedef struct s_entry	t_entry;

void		get_rights(t_file *file, struct stat stats);
void		get_id(t_file *file, struct stat stats);
void		get_size(t_file *file, struct stat stats);
void		get_date(t_file *file, struct stat stats, int flags);

#endif
