/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: breda-si <breda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:02:12 by breda-si          #+#    #+#             */
/*   Updated: 2025/04/05 14:04:32 by breda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_split_tokens(t_token *start, t_token *aux,
	t_token **left, t_token **right)
{
	*left = NULL;
	*right = NULL;
	if (aux->prev)
	{
		*left = start;
		aux->prev->next = NULL;
	}
	if (aux->next)
	{
		*right = aux->next;
		aux->next->prev = NULL;
	}
}

void	*ft_pipe(t_token *start, t_token *aux, t_minishell *bash)
{
	t_pipe	*pipe;
	t_token	*left;
	t_token	*right;

	if (!aux)
		return (NULL);
	pipe = malloc(sizeof(t_pipe));
	if (!pipe)
		return (NULL);
	ft_split_tokens(start, aux, &left, &right);
	free_token(aux);
	pipe->type = PIPE;
	pipe->left = ft_tree(left, bash);
	pipe->right = ft_tree(right, bash);
	return (pipe);
}
