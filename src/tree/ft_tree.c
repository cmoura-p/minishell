/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: breda-si <breda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:48:17 by brendon           #+#    #+#             */
/*   Updated: 2025/04/05 14:05:39 by breda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*find_token_by_type(t_token *start, enum e_type type)
{
	t_token	*aux;

	aux = start;
	while (aux && aux->type != type)
		aux = aux->next;
	return (aux);
}

void	*handle_command(t_token *start)
{
	t_exec	*root;

	root = malloc(sizeof(t_exec));
	if (!root)
		return (NULL);
	root->type = COMMAND;
	root->args = tokken_to_args(start);
	free_token_list(start);
	return (root);
}

t_token	*find_redir(t_token *start)
{
	t_token	*aux;

	aux = start;
	while (aux && aux->type != REDIR_IN && aux->type != REDIR_OUT
		&& aux->type != REDIR_APP)
		aux = aux->next;
	return (aux);
}

void	*ft_tree(t_token *start, t_minishell *bash)
{
	t_token	*aux;

	if (!start)
		return (NULL);
	aux = find_token_by_type(start, PIPE);
	if (aux)
		return (ft_pipe(start, aux, bash));
	aux = find_redir(start);
	if (aux)
	{
		if (aux->type == REDIR_IN)
			return (ft_redir_in(start, aux, bash));
		else if (aux->type == REDIR_OUT)
			return (ft_redir_out(start, aux, bash));
		else if (aux->type == REDIR_APP)
			return (ft_redir_app(start, aux, bash));
	}
	return (handle_command(start));
}
