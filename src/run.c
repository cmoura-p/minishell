/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 23:00:17 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/02/23 09:20:13 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	run(t_minishell *bash)
{
	tokenizer(bash);
	parsing(bash);
    if (!bash->token)
		return;
	init_signals();
	bash->root = ft_tree(bash->token, bash);
	if (!bash->root)
		return;
	ft_execute(bash, bash->root);
	ft_free_tree(bash->root);
	//free_token_list(bash->token);
    free_to_restart(bash);
	bash->token = NULL;
}
