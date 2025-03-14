/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplicate_token_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: breda-si <breda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:02:49 by breda-si          #+#    #+#             */
/*   Updated: 2025/03/14 17:24:17 by breda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*create_new_token(t_token *token)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = token->type;
	new_token->status = token->status;
	new_token->i = token->i;
	new_token->name = ft_strdup(token->name);
	new_token->env_null = ft_strdup(token->env_null);
	new_token->expand = token->expand;
	new_token->prev = NULL;
	new_token->next = NULL;
	return (new_token);
}

t_token	*duplicate_token(t_token *token)
{
	if (!token)
		return (NULL);
	return (create_new_token(token));
}

void	handle_new_token(t_token **new_head, t_token **prev, t_token *new_token)
{
	if (!*new_head)
		*new_head = new_token;
	if (*prev)
		(*prev)->next = new_token;
	new_token->prev = *prev;
	*prev = new_token;
}

t_token	*duplicate_token_list(t_token *head)
{
	t_token		*new_head;
	t_token		*new_token;
	t_token		*current;
	t_token		*prev;

	new_head = NULL;
	current = head;
	prev = NULL;
	while (current)
	{
		new_token = duplicate_token(current);
		if (!new_token)
		{
			free_token_list(new_head);
			return (NULL);
		}
		handle_new_token(&new_head, &prev, new_token);
		current = current->next;
	}
	return (new_head);
}
