/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_app.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: breda-si <breda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:02:26 by breda-si          #+#    #+#             */
/*   Updated: 2025/04/10 01:19:33 by breda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*ft_redir_app(t_token *start, t_token *aux, t_minishell *bash)
{
	t_redir	*redir;

	if (!aux || ft_ambiguous_redir(aux, bash))
	{
		free_token_list(start);
		return (NULL);
	}
	redir = ft_init_redir(REDIR_APP, aux);
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
