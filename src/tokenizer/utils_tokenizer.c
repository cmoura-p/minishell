/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@students.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 09:26:41 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/03/06 16:23:13 by cmoura-p         ###   ########.fr       */
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

	newtoken = ft_calloc(1, sizeof(t_token));
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

void	add_tokenlst_dq(t_minishell *bash, t_token **aux, \
		char *name, enum e_type type)
{
	t_token	*newtoken;

	newtoken = ft_calloc(1, sizeof(t_token));
	if (!newtoken)
		return ;
	newtoken->name = name;
	newtoken->type = type;
	newtoken->status = NO_QUOTE;
	if ((*aux)->prev)
	{
		(*aux)->prev->next = newtoken;
		newtoken->prev = (*aux)->prev;
		(*aux)->prev = newtoken;
		newtoken->next = (*aux);
	}
	else
	{
		(*aux)->prev = newtoken;
		newtoken->prev = NULL;
		newtoken->next = (*aux);
		bash->token = newtoken;
	}
}

void	del_tokenlst(t_minishell *bash, t_token **token)
{
	t_token	*aux;

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
	if ((!(*token)->next) && (*token)->type != EXP_EXIT)
	{
		(*token)->status = NO_QUOTE;
		(*token)->type = WORD;
	}
}

void	fix_a_var(char **a_var)
{
	char	*temp;

	if (!(*a_var))
		return ;
	temp = ft_substr((*a_var), 1, ft_strlen((*a_var)) - 1);
	if (!temp)
		return ;
	free(*a_var);
	(*a_var) = temp;
}

