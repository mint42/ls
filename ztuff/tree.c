/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 15:48:45 by rreedy            #+#    #+#             */
/*   Updated: 2019/01/22 15:48:47 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

typedef struct				s_binarytree
{
	void					*content;
	struct	s_binarytree	*left;
	struct	s_binarytree	*right;
}							t_binarytree;

void	ft_treeadd(t_binarytree **binarytree, t_binarytree *node)
{
	
}

void	ft_treedel(t_binarytree **binarytree, void (*del)(void *))
{
	if ((*binarytree)->left)
		ft_treedel(&(*binarytree)->left, del);
	ft_treedelone(binarytree, del);
	if ((*binarytree)->right)
		ft_treedel(&(*binarytree)->right, del);
}

void	ft_treedelone(t_binarytree **node, void (*del)(void *))
{
	del((*binarytree)->content);
	ft_memdel((void **)node);
}

void	ft_treeiter(t_binarytree *binarytree, void (*f)(t_list *node))
{
	if (binarytree->left)
		ft_treeiter(binarytree->left, f);
	f(binarytree);
	if (binarytree->right)
		ft_treeiter(binarytree->right, f);
}

t_list	*ft_treemap(t_binarytree *tree, t_binarytree *(*f)(t_list *node))
{

}

t_list	*ft_treenew(void const *content, size_t content_size)
{
	t_binarytree	*node;

	node = 
}
