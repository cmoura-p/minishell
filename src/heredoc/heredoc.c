/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 22:33:00 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/01/27 01:10:05 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_heredoc(t_minishell *bash)
{
	t_heredoc	*heredoc;

	heredoc = ft_calloc(1, sizeof(t_heredoc));
	if (!heredoc)
		return;
	heredoc->fd_heredoc = 0;
	heredoc->heredoc_path = NULL;
	heredoc->eo_heredoc = NULL;
	heredoc->i = 0;
	heredoc->next = NULL;
	bash->heredoc = heredoc;
}
