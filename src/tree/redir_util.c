/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: breda-si <breda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 14:23:17 by breda-si          #+#    #+#             */
/*   Updated: 2025/04/05 17:56:55 by breda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_ambiguous_redir(t_token *aux, t_minishell *bash)
{
	if (aux->next->type == EXP_NULL)
	{
		ft_fprintf(STDERR_FILENO, "minishell: %s: ambiguous redirect\n",
			aux->next->env_null);
		bash->exit_status = 1;
		return (1);
	}
	return (0);
}

t_redir	*ft_init_redir(enum e_type type, t_token *aux)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file_name = ft_strdup(aux->next->name);
	if (type == REDIR_APP)
		redir->fd = open(redir->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (type == REDIR_IN)
		redir->fd = open(redir->file_name, O_RDONLY);
	else
		redir->fd = open(redir->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (redir);
}
