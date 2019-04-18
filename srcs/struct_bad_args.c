/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_bad_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:55:44 by rreedy            #+#    #+#             */
/*   Updated: 2019/04/16 02:22:13 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bad_arg.h"
#include "compare.h"
#include "ft_mem.h"
#include "ft_str.h"
#include "ft_binarytree.h"
#include "ft_printf.h"
#include <errno.h>
#include <string.h>

t_bad_arg	*init_bad_arg(char *path)
{
	t_bad_arg	*bad_arg;

	bad_arg = (t_bad_arg *)ft_memalloc(sizeof(t_bad_arg));
	bad_arg->error_message = ft_strdup(strerror(errno));
	bad_arg->path = path;
	return (bad_arg);
}

void		insert_bad_arg(t_binarytree **bad_args, t_bad_arg *content,
				int (*compare)())
{
	if (!*bad_args)
		*bad_args = ft_treeinit(content, 0);
	else
	{
		if ((compare((t_cmp *)content, (t_cmp *)T_BAD_ARG(*bad_args))) >= 0)
			insert_bad_arg(&(*bad_args)->right, content, compare);
		else
			insert_bad_arg(&(*bad_args)->left, content, compare);
	}
}

void		print_bad_arg(t_binarytree *node)
{
	t_bad_arg	bad_arg;

	bad_arg = *T_BAD_ARG(node);
	ft_printfd(2, "ft_ls: %s: %s\n", bad_arg.path, bad_arg.error_message);
}

void		delete_bad_arg(void *content, size_t content_size)
{
	(void)content_size;
	if (content)
	{
		ft_strdel(&((t_bad_arg *)(content))->path);
		ft_strdel(&((t_bad_arg *)(content))->error_message);
		ft_memdel((void **)&content);
	}
}
