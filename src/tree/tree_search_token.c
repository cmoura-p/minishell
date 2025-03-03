/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_search_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brendon <brendon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:48:22 by brendon           #+#    #+#             */
/*   Updated: 2025/03/03 11:48:23 by brendon          ###   ########.fr       */
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

void	*handle_pipe(t_token *start, t_token *aux, t_minishell *bash)
{
	return (ft_pipe(start, aux, bash));
}

void	*handle_redir_in(t_token *start, t_token *aux, t_minishell *bash)
{
	return (ft_redir_in(start, aux, bash));
}

void	*handle_redir_out(t_token *start, t_token *aux, t_minishell *bash)
{
	return (ft_redir_out(start, aux, bash));
}

void	*handle_redir_app(t_token *start, t_token *aux, t_minishell *bash)
{
	return (ft_redir_app(start, aux, bash));
}
