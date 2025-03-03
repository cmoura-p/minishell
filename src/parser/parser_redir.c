/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:19:54 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/03/01 21:02:39 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_redir(t_minishell *bash)
{
	t_token	*aux;

	aux = bash->token;
	while (aux)
	{
		if (aux->type == REDIR_IN)
			aux = set_redir_file(aux, FILE_IN);
		else if (aux->type == REDIR_OUT)
			aux = set_redir_file(aux, FILE_OUT);
		else if (aux->type == REDIR_APP)
			aux = set_redir_file(aux, FILE_APP);
		else
			aux = aux->next;
	}
}

t_token	*set_redir_file(t_token *token, enum e_type type)
{
	token = token->next;
	if (token->type == BLANK)
		token = token->next;
	while (token && token->type == WORD)
	{
		token->type = type;
		token = token->next;
	}
	return (token);
}
