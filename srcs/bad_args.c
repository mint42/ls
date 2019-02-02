/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bad_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 15:18:33 by rreedy            #+#    #+#             */
/*   Updated: 2019/02/01 17:41:46 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_bad_arg	init_bad_arg(char *name)
{
	t_bad_arg	bad_arg;

	bad_arg.error_message = ft_strdup(strerror(errno));
	bad_arg.name = ft_strdup(name);
	return (bad_arg);
}

void		insert_bad_arg(t_binarytree **bad_args, t_bad_arg content,
				int (*compare)(char *s1, char *s2))
{
	if (!*bad_args)
		*bad_args = ft_treenew(&content);
	else
	{
		if ((compare(T_BAD_ARG(*bad_args)->name, content.name)) >= 0)
			insert_bad_arg(&(*bad_args)->right, content, compare);
		else
			insert_bad_arg(&(*bad_args)->left, content, compare);
	}
}

void		print_bad_arg(t_bad_arg *bad_arg)
{
	ft_printf("ls: %s %s\n", bad_arg->name, bad_arg->error_message);
}

void		delete_bad_arg(t_bad_arg *bad_arg)
{
	ft_strdel(&(bad_arg->name));
	ft_strdel(&(bad_arg->error_message));
}
