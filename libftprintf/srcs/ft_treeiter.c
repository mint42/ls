/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treeiter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 12:52:16 by rreedy            #+#    #+#             */
/*   Updated: 2019/02/07 12:56:29 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_treeiter(t_binarytree *binarytree, void (*f)())
{
	if (binarytree->left)
		ft_treeiter(binarytree->left, f);
	f(binarytree);
	if (binarytree->right)
		ft_treeiter(binarytree->right, f);
}
