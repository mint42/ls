/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 15:56:35 by rreedy            #+#    #+#             */
/*   Updated: 2019/02/25 17:10:22 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char		*color_code(char *name, char **list, char *color_code)
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
			return (color_code);
		++(extension);
	}
	return (COLOR_REG);
}

char			*get_color(t_file *file)
{
	char	*color;

	if (!ft_strequ(file->color, COLOR_REG))
		return (file->color);
	color = color_code(file->name, g_img_extensions, COLOR_IMG);
	if (!ft_strequ(color, COLOR_REG))
		return (color);
	color = color_code(file->name, g_zip_extensions, COLOR_ZIP);
	if (!ft_strequ(color, COLOR_REG))
		return (color);
	color = color_code(file->name, g_dot_c, COLOR_DOTC);
	if (!ft_strequ(color, COLOR_REG))
		return (color);
	return (file->color);
}
