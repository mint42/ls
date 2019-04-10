/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 15:56:35 by rreedy            #+#    #+#             */
/*   Updated: 2019/04/09 18:53:32 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"
#include "colors.h"
#include "libft.h"

static char		*color_file_type(char c)
{
	if (c == 'b')
		return (COLOR_BLK);
	else if (c == 'c')
		return (COLOR_CHR);
	else if (c == 'd')
		return (COLOR_DIR);
	else if (c == 'l')
		return (COLOR_LNK);
	else if (c == 'p')
		return (COLOR_FIF);
	else if (c == 's')
		return (COLOR_SOC);
	return (0);
}

static int		color_ext(char *name, char **list)
{
	char	**extension;
	size_t	strlen;
	size_t	extlen;

	extension = list;
	strlen = ft_strlen(name);
	extlen = 0;
	while (extension && *extension)
	{
		extlen = ft_strlen(*extension);
		if (ft_strequ(name + strlen - extlen, *extension))
			return (1);
		++(extension);
	}
	return (0);
}

char			*get_color(t_file *file)
{
	char	*color;

	color = color_file_type(file->rights[0]);
	if (color)
		return (color);
	if (file->rights[1] == 'x' || file->rights[1] == 's' ||
		file->rights[3] == 'x' || file->rights[3] == 's' ||
		file->rights[9] == 'x' || file->rights[9] == 's' ||
		file->rights[9] == 't')
	{
		return (COLOR_EXE);
	}
	if (color_ext(file->name, g_img_extensions))
		return (COLOR_IMG);
	if (color_ext(file->name, g_zip_extensions))
		return (COLOR_ZIP);
	if (color_ext(file->name, g_src_extensions))
		return (COLOR_SRC);
	return (COLOR_REG);
}
