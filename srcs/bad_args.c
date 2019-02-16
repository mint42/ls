/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bad_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 15:18:33 by rreedy            #+#    #+#             */
/*   Updated: 2019/02/15 13:22:07 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_bad_arg	*fill_bad_arg(char *name)
{
	t_bad_arg	*bad_arg;

	bad_arg = (t_bad_arg *)ft_memalloc(sizeof(t_bad_arg));
	bad_arg->error_message = ft_strdup(strerror(errno));
	bad_arg->name = name;
	return (bad_arg);
}

void		insert_bad_arg(t_binarytree **bad_args, t_bad_arg *content,
				int (*compare)(char *s1, char *s2))
{
	if (!*bad_args)
		*bad_args = ft_treenew(content);
	else
	{
		if ((compare(content->name, T_BAD_ARG(*bad_args)->name)) >= 0)
			insert_bad_arg(&(*bad_args)->right, content, compare);
		else
			insert_bad_arg(&(*bad_args)->left, content, compare);
	}
}

void		print_bad_arg(t_binarytree *node)
{
	t_bad_arg	bad_arg;

	bad_arg = *T_BAD_ARG(node);
	ft_printfd(2, "ft_ls: %s: %s\n", bad_arg.name, bad_arg.error_message);
}

void		delete_bad_arg(t_bad_arg **bad_arg)
{
	ft_strdel(&((*bad_arg)->name));
	ft_strdel(&((*bad_arg)->error_message));
	ft_memdel((void **)bad_arg);
}
