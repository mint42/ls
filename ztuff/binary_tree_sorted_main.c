#include <time.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include "ft_printf.h"

typedef struct			s_binarytree
{
	char				*name;
	struct s_binarytree	*left;
	struct s_binarytree	*right;
}						t_binarytree;

typedef struct			s_dir
{
	char				*path;
	unsigned int		username_len;
	unsigned int		groupname_len;
	unsigned int		links_len;
	unsigned int		bytes_len;
}						t_dir;

typedef struct			s_file
{
	char				*name;
	char				*path;
	char				*rights;
	char				*username;
	char				*groupname;
	char				*date;
	unsigned int		links;
	unsigned long int	bytes;
}						t_file;

void	ft_treedelone(t_binarytree **node, void (*del)(char **))
{
	del(&(*node)->name);
	ft_memdel((void **)node);
}

void	ft_treedel(t_binarytree **binarytree, void (*del)(char **))
{
	if ((*binarytree)->left)
		ft_treedel(&(*binarytree)->left, del);
	if ((*binarytree)->right)
		ft_treedel(&(*binarytree)->right, del);
	ft_treedelone(binarytree, del);
}

void			treeprint(t_binarytree *binarytree)
{
	if (binarytree->left)
		treeprint(binarytree->left);
	ft_printf("%s\n", binarytree->name);
	if (binarytree->right)
		treeprint(binarytree->right);
}

t_binarytree	*new_node(char *name)
{
	t_binarytree	*node;

	node = (t_binarytree *)malloc(sizeof(t_binarytree));
	node->name = name;
	node->left = 0;
	node->right = 0;
	return (node);
}

void			insert(t_binarytree **binarytree, char *name)
{
	if (!(*binarytree))
		*binarytree = new_node(name);
	else
	{
		if (ft_strcmp(name, (*binarytree)->name) >= 0)
			insert(&(*binarytree)->right, name);
		else 
			insert(&(*binarytree)->left, name);
	}
}

int main(int argc, char **argv)
{
	t_binarytree	*binarytree;
	struct dirent	*dirent;
	DIR				*dirp;

	(void)argc;
	++argv;
	binarytree = 0;
	dirp = opendir(*argv);
	while ((dirent = readdir(dirp)))
		insert(&binarytree,ft_strdup( dirent->d_name));
	treeprint(binarytree);
	ft_treedel(&binarytree, ft_strdel);
	(void)closedir(dirp);
	return (0);
}
