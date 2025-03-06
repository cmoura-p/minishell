#include "../../include/minishell.h"

void	*ft_redir_out(t_token *start, t_token *aux, t_minishell *bash)
{
	t_redir	*redir;

	if (!aux || !aux->next)
		return (free_null_redir(aux));
	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (free_null_redir(aux));
	redir->type = REDIR_OUT;
	redir->file_name = ft_strdup(aux->next->name);
	redir->fd = open(redir->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redir->fd < 0)
		return (handle_redir_error(redir, bash, aux));
	if (!aux->prev && aux->next->next)
		start = aux->next->next;
	else if (!aux->prev && !aux->next->next)
	{
		free_null_redir(aux);
		redir->next = ft_tree(NULL, bash);
		return (redir);
	}
	ft_remove_tokens(aux);
	if (start)
		redir->next = ft_tree(start, bash);
	return (redir);
}
