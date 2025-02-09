/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:39:01 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/01/27 19:28:49 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void jointokens(t_minishell *bash)
{
	t_token *aux;
	char	*newname;

	aux = bash->token;
	while(aux)
	{
		if ((aux->status != NO_QUOTE) && (((aux->prev != NULL) && (aux->prev->type == WORD))
			|| ((aux->next != NULL) && (aux->next->type == WORD))))
		{
			if ((aux->prev != NULL) && (aux->prev->type == WORD))
			{
				newname = ft_strjoin(aux->prev->name, aux->name);
				joinprev(&aux, newname);
			}
			else if ((aux->next != NULL) && (aux->next->type == WORD))
			{
				newname = ft_strjoin(aux->name, aux->next->name);
				joinnext(&aux, newname);
			}
			aux = bash->token;
		}
		else
			aux = aux->next;
	}
}

void joinnext(t_token **token, char *name)
{
	t_token	*aux;
	t_token	*aux_next;

	aux = (*token);
	aux_next = (*token)->next;
	aux->name = name;
	aux->status = aux_next->status;
	aux->type = aux->next->type;
	aux->next = aux_next->next;
	if (aux_next->next != NULL)
		aux_next->next->prev = aux_next->prev;
	if (aux_next->name)
		free(aux_next->name);
	free(aux_next);
}

void joinprev(t_token **token, char *name)
{
	t_token	*aux;
	t_token	*aux_prev;

	aux = (*token);
	aux_prev = (*token)->prev;
	aux_prev->name = name;
	if ((aux->next) && (aux->next->type == WORD))
		aux_prev->status = aux->status;
	aux_prev->next = aux->next;
	if (aux->next != NULL)
		aux->next->prev = aux->prev;
	if (aux->name)
		free(aux->name);
	free(aux);
}

void jointokens(t_minishell *bash)
{
	t_token *aux;
	char	*newname;

	aux = bash->token;
	while(aux)
	{
		if ((aux->status != NO_QUOTE) && (((aux->next != NULL) && (aux->next->type == WORD))
			|| ((aux->prev != NULL) && aux->prev->type == WORD)))
		{
			if ((aux->i == 0) && (aux->next->type == WORD))
			{
				newname = ft_strjoin(aux->name, aux->next->name);
				joinnext(&aux, newname);
			}
			else if ((aux->i != 0) && (aux->prev->type == WORD))
			{
				newname = ft_strjoin(aux->prev->name, aux->name);
				joinprev(&aux, newname);
			}
			aux = bash->token;
		}
		else
			aux = aux->next;
	}
}
void joinexpand(t_token **token, char *name, char *name_exp)
{
	t_token	*aux;
	t_token	*aux_next;
	char	*sobra;

	sobra = NULL;
	aux = (*token);
	sobra = ft_substr((aux->next->name), (ft_strlen(name)), \
			(ft_strlen(aux->next->name)-1));
	aux->name = ft_strjoin(name_exp, sobra);
	aux_next = aux->next;
	aux->type = aux_next->type;
	aux->status = aux_next->status;
	aux->next = aux_next->next;
	if (aux_next->next != NULL)
		aux_next->next->prev = aux_next->prev;
	if (aux_next->name)
		free(aux_next->name);
	free(aux_next);
}
void joinexpand_dq(t_token **token, char *after, char *before, char *name_exp)
{
	t_token	*aux;
	t_token	*aux_next;

	name_exp = ft_strjoin(before, name_exp);
	aux = (*token);
	aux->name = ft_strjoin(name_exp, after);
	if ((aux->next != NULL) && (aux->next->type == WORD))
	{
		aux_next = aux->next;
		aux->status = aux_next->status;
		aux->next = aux_next->next;
		if (aux_next->next != NULL)
			aux_next->next->prev = aux_next->prev;
		free(aux_next);
	}
	aux->type = ARGUMENT;
}
