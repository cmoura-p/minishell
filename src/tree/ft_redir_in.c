/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@students.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:02:22 by breda-si          #+#    #+#             */
/*   Updated: 2025/04/12 16:10:13 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*ft_redir_in(t_token *start, t_token *aux, t_minishell *bash)
{
	t_redir	*redir;

	if (!aux || ft_ambiguous_redir(aux, bash))
	{
		free_token_list(start);
		return (NULL);
	}
	redir = ft_init_redir(REDIR_IN, aux);
	if (!redir)
		return (free_null_redir(aux));
	if (redir->fd < 0)
		return (handle_redir_error(redir, bash, start));
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
