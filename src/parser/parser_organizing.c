/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_organizing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@students.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:59:59 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/03/13 18:06:40 by cmoura-p         ###   ########.fr       */
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
		if ((not_redirection(aux) && (aux->type == WORD)))
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
	{
		if (aux->type == WORD && aux->prev && aux->prev->type == COMMAND)
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
			if (aux->env_null)
				free(aux->env_null);
			free(aux);
		}
		aux = aux_next;
	}
}

int	not_redirection(t_token *token)
{
	if (token->prev == NULL)
		return (1);
	if ((token->prev->type == REDIR_IN) || (token->prev->type == REDIR_OUT)
		|| (token->prev->type == REDIR_APP) || (token->prev->type == HEREDOC))
		return (0);
	return (1);
}
