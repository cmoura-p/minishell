/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 09:26:41 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/01/25 19:49:58 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_tokenlst_back(t_token **newtoken, t_token *lst)
{
	while (lst->next)
		lst = lst->next;
	lst->next = *newtoken;
	(*newtoken)->i = lst->i + 1;
	(*newtoken)->prev = lst;
}

void	add_tokenlst(t_minishell **bash, char *name, \
			enum e_type type, enum e_status status_q)
{
	t_token	*newtoken;
	t_token	*aux;

	newtoken = (t_token *)malloc(sizeof(t_token));
	if (!newtoken)
		return ;
	newtoken->name = name;
	newtoken->type = type;
	newtoken->status = status_q;
	if (!(*bash)->token)
	{
		(*bash)->token = newtoken;
		(*bash)->token->i = 0;
		(*bash)->token->prev = NULL;
	}
	else
	{
		aux = (*bash)->token;
		add_tokenlst_back(&newtoken, aux);
	}
	newtoken->next = NULL;
}

void	add_tokenlst_mid(t_minishell *bash, t_token **aux, char *name, \
			enum e_type type, enum e_status status_q)
{
	t_token	*newtoken;

	newtoken = (t_token *)malloc(sizeof(t_token));
	if (!newtoken)
		return ;
	newtoken->name = name;
	newtoken->type = type;
	newtoken->status = status_q;
	if ((*aux)->next)
	{
		newtoken->next = (*aux)->next;
		(*aux)->next->prev = newtoken;
	}
	else
		newtoken->next = (*aux);
	if ((*aux)->prev)
	{
		newtoken->prev = (*aux)->prev;
		(*aux)->prev->next = newtoken;
	}
	(*aux)->prev = newtoken;
	if (!(*aux)->prev)
		bash->token = newtoken;
}
void	del_tokenlst(t_minishell *bash, t_token **token)
{
	t_token *aux;

	aux = *token;

	if (aux == bash->token)
		bash->token = aux->next;
	if (aux->prev)
		aux->prev->next = aux->next;
	if (aux->next)
	{
		aux->next->prev = aux->prev;
		*token = aux->next;
	}
	else
		*token = aux->prev;
	if (aux->name)
		free(aux->name);
	free(aux);
	if (!(*token)->next)
	{
		(*token)->type = WORD;
		(*token)->status = NO_QUOTE;
	}
}
