/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@students.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:39:01 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/03/19 17:09:58 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	jointokens(t_minishell *bash)
{
	t_token	*aux;
	char	*newname;

	aux = bash->token;
	while (aux)
	{
		if ((aux->type == WORD) && (((aux->prev != NULL) \
			&& (aux->prev->type == WORD)) || ((aux->next != NULL) \
			&& (aux->next->type == WORD))))
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

void	joinnext(t_token **token, char *name)
{
	t_token	*aux;
	t_token	*aux_next;

	aux = (*token);
	aux_next = (*token)->next;
	free(aux->name);
	aux->name = name;
    if ((checked_for_hd(aux) == 1) && (aux->status == DOUBLE_Q))
        aux_next->status = DOUBLE_Q;
    aux->status = aux_next->status;
	aux->type = aux->next->type;
	aux->next = aux_next->next;
	if (aux_next->next != NULL)
		aux_next->next->prev = aux_next->prev;
	if (aux_next->name)
		free(aux_next->name);
	if (aux_next->env_null)
		free(aux_next->env_null);
	free(aux_next);
}

void	joinprev(t_token **token, char *name)
{
	t_token	*aux;
	t_token	*aux_prev;

	aux = (*token);
	aux_prev = aux->prev;
	free(aux_prev->name);
	aux_prev->name = name;
	if ((aux->next) && aux->next->type == WORD && aux->type == WORD)
		aux_prev->status = aux->status;
	aux_prev->next = aux->next;
	if (aux->next != NULL)
		aux->next->prev = aux->prev;
	if (aux->name)
		free(aux->name);
	if (aux->env_null)
		free(aux->env_null);
	free(aux);
	(*token) = aux_prev;
}

void	joinexpand(t_token **token, char *name, char *name_exp)
{
	t_token	*aux;
	t_token	*aux_next;
	char	*sobra;

	sobra = NULL;
	aux = (*token);
	sobra = ft_substr((aux->next->name), (ft_strlen(name)), \
			(ft_strlen(aux->next->name) - 1));
	free(aux->name);
	aux->name = ft_strjoin(name_exp, sobra);
	free(sobra);
	aux_next = aux->next;
	if ((aux->name[0] == '\0') && (aux_next->status != SINGLE_Q))
		aux->type = EXP_NULL;
	else
		aux->type = aux_next->type;
	aux->status = aux_next->status;
	aux->next = aux_next->next;
	if (aux_next->next != NULL)
		aux_next->next->prev = aux_next->prev;
	if (aux_next->name)
		free(aux_next->name);
	if (aux_next->env_null)
		free(aux_next->env_null);
	free(aux_next);
}

void	remove_exp_null(t_minishell *bash)
{
	t_token	*aux;
	t_token	*aux_next;

	aux = bash->token;
	while (aux)
	{
		aux_next = aux->next;
		if ((aux->type == EXP_NULL) && (ok_with_redir(aux)))
		{
			if (!aux->prev)
				bash->token = aux->next;
			else
				aux->prev->next = aux->next;
			if (aux->next)
				aux->next->prev = aux->prev;
			if (aux->name)
				free(aux->name);
			if (aux->env_null)
				free(aux->env_null);
			free(aux);
		}
		aux = aux_next;
	}
}
