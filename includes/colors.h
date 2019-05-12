/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 17:43:27 by rreedy            #+#    #+#             */
/*   Updated: 2019/04/23 07:51:11 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# define COLOR_REG "\e[m"
# define COLOR_DIR "\e[1;33m"
# define COLOR_LNK "\e[0;31m"
# define COLOR_BLK "\e[1;34m"
# define COLOR_CHR "\e[0;34m"
# define COLOR_FIF "\e[0;36m"
# define COLOR_SOC "\e[0;36m"
# define COLOR_EXE "\e[1;35m"
# define COLOR_IMG "\e[0;31m"
# define COLOR_ZIP "\e[1;36m"
# define COLOR_SRC "\e[1;32m"

static const char	*g_img_extensions[7] =
{
	".bmp",
	".gif",
	".jpeg",
	".jpg",
	".png",
	".tiff",
	0,
};

static const char	*g_zip_extensions[8] =
{
	".7z",
	".gz",
	".rar",
	".tar",
	".tar.gz",
	".tgz",
	".zip",
	0,
};

static const char	*g_src_extensions[2] =
{
	".c",
	0,
};

char			*get_color(t_file *file);

#endif
