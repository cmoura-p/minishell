/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@students.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 23:00:17 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/03/05 18:15:17 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	run(t_minishell *bash)
{
	tokenizer(bash);
	print_token_list(bash->token);
	parsing(bash);
	if (!bash->token)
		return ;
	print_token_list(bash->token);
	init_signals();
	bash->root = ft_tree(duplicate_token_list(bash->token), bash);
	if (!bash->root)
	{
		free_to_restart(bash);
		return ;
	}
	ft_execute(bash, bash->root);
	ft_free_tree(bash->root);
	free_to_restart(bash);
}
