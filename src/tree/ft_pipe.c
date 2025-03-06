#include "../../include/minishell.h"

void	*ft_pipe(t_token *start, t_token *aux, t_minishell *bash)
{
	t_pipe	*pipe;
	t_token	*left;
	t_token	*right;

	if (!aux || !aux->next)
		return (NULL);
	pipe = malloc(sizeof(t_pipe));
	if (!pipe)
		return (NULL);
	left = start;
	right = aux->next;
	if (aux->prev)
		aux->prev->next = NULL;
	if (aux->next)
		aux->next->prev = NULL;
	free_token(aux);
	pipe->type = PIPE;
	pipe->left = ft_tree(left, bash);
	pipe->right = ft_tree(right, bash);
	return (pipe);
}
