/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brendon <brendon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:48:17 by brendon           #+#    #+#             */
/*   Updated: 2025/03/03 11:48:18 by brendon          ###   ########.fr       */
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

void	*ft_tree(t_token *start, t_minishell *bash)
{
	t_token	*aux;

	if (!start)
		return (NULL);
	aux = find_token_by_type(start, PIPE);
	if (aux)
		return (ft_pipe(start, aux, bash));
	aux = find_token_by_type(start, REDIR_IN);
	if (aux)
		return (ft_redir_in(start, aux, bash));
	aux = find_token_by_type(start, REDIR_OUT);
	if (aux)
		return (ft_redir_out(start, aux, bash));
	aux = find_token_by_type(start, REDIR_APP);
	if (aux)
		return (ft_redir_app(start, aux, bash));
	return (handle_command(start));
}
