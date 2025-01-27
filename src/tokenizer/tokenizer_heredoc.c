/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 20:47:23 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/01/27 00:51:06 by cmoura-p         ###   ########.fr       */
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
	bash->heredoc->i++;
	return (i+1);
}
