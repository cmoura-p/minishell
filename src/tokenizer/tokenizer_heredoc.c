/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 20:47:23 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/01/29 17:30:30 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	token_heredoc(char *line, int i, t_minishell *bash)
{
	if (!line)
		return (1);
	if (!bash->heredoc)
		init_heredoc(bash);
	add_tokenlst(&bash, ft_strdup("<<"), HEREDOC, NO_QUOTE);
	return (i+1);
}
void	init_heredoc(t_minishell *bash)
{
	t_heredoc	*heredoc;

	heredoc = ft_calloc(1, sizeof(t_heredoc));
	if (!heredoc)
		return;
	heredoc->fd_heredoc = 0;
	heredoc->eo_heredoc = NULL;
	heredoc->hd_path = NULL;
	heredoc->status = NO_QUOTE;
	heredoc->counter = 1;
	heredoc->next = NULL;
	bash->heredoc = heredoc;
}

