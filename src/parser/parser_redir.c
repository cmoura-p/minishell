/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:19:54 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/01/25 19:46:03 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_redir(t_minishell *bash)
{
	t_token	*aux;

	aux = bash->token;
	while (aux)
	{
		if (aux->type == BLANK)
			aux = aux->next;
		if (aux->type == REDIR_IN)
			aux->next->type = FILE_IN;
		else if (aux->type == REDIR_OUT)
			aux->next->type = FILE_OUT;
		else if (aux->type == REDIR_APP)
			aux->next->type = FILE_APP;
	aux = aux->next;
	}
}

