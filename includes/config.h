/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 17:04:27 by rreedy            #+#    #+#             */
/*   Updated: 2019/02/20 17:38:48 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include "ft_ls.h"

# define COLOR_REG "\e[m"
# define COLOR_DIR "\e[1;33m"
# define COLOR_LNK "\e[1;35m"
# define COLOR_EXE "\e[1;32m"
# define COLOR_IMG "\e[0;33m"
# define COLOR_ZIP "\e[1;36m"
//# define IMG_EXTENSIONS ".png:.jpg:.jpeg:.gif:.bmp:.tiff"
//# define ZIP_EXTENSIONS ".tar:.gz:.tar.gz:.zip:.rar:.7z"

static char		*g_img_extensions[7] = 
{
	".bmp",
	".gif",
	".jpeg",
	".jpg",
	".png",
	".tiff",
	0,
};

static char		*g_zip_extensions[7] =
{
	".7z",
	".gz",
	".rar",
	".tar",
	".tar.gz",
	".zip",
	0,
};
#endif
