/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@students.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 23:00:17 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/02/15 16:06:54 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	run(t_minishell *bash)
{
	tokenizer(bash);
	print_token_list(bash->token);
	parsing(bash);
    if (!bash->token)
        return;
    init_signals();
//	bash->root = ft_tree(bash->token);
//	if (!bash->root)
//		return;
//	ft_execute(bash, bash->root);
//	ft_free_tree(bash->root);
//	free_token_list(bash->token);
//	bash->token = NULL;
    free_to_restart(bash);
}
