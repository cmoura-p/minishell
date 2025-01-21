/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_organizing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:59:59 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/01/21 01:21:10 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_commands(t_minishell *bash)
{
	t_token	*aux;
	t_token	*aux_next;

	aux = bash->token;
	while (aux)
	{
		aux_next = aux->next;
		if (aux->type == WORD)
		{
			aux->type = COMMAND;
			while (aux_next && aux_next->type == WORD)
			{
				aux = aux_next;
				aux_next = aux_next->next;
				aux->type = COMMAND;
			}
			find_a_pipe(&aux_next);
		}
		aux = aux_next;
	}
}

void	set_arguments(t_minishell *bash)
{
	t_token	*aux;

	aux = bash->token;
	while (aux)
	{					// esse if nao ta fazendo o papel
		if (aux->type == WORD
			|| (aux->next && aux->next->type == WORD))
		{
			aux->type = ARGUMENT;
			while (aux->next && aux->next->type == WORD)
			{
				aux = aux->next;
				aux->type = ARGUMENT;
			}
		}
		aux = aux->next;
	}
}
void	find_a_pipe(t_token **aux)
{
	while (*aux && (*aux)->type != PIPE)
		*aux = (*aux)->next;
	if (*aux)
		*aux = (*aux)->next;
}
void	remove_blank(t_minishell *bash)
{
	t_token	*aux;
	t_token	*aux_next;

	aux = bash->token;
	while (aux)
	{
		aux_next = aux->next;
		if (aux->type == BLANK)
		{
			if (aux == bash->token)
				bash->token = aux_next;
			if (!aux->prev)
				bash->token = aux->next;
			else
				aux->prev->next = aux->next;
			if (aux->next)
				aux->next->prev = aux->prev;
			if (aux->name)
				free(aux->name);
			free(aux);
		}
		aux = aux_next;
	}
}
