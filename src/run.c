/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@students.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 23:00:17 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/04/10 09:04:48 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	run(t_minishell *bash)
{
	t_token	*aux;

	tokenizer(bash);
	ft_printf("Tokenizer\n");
	print_token_list(bash->token);
	parsing(bash);
	if (!bash->token)
		return ;
	init_signals();
	aux = bash->token;
	bash->root = ft_tree(duplicate_token_list(aux), bash);
	if (!bash->root)
	{
		free_to_restart(bash);
		return ;
	}
	ft_execute(bash, bash->root);
	ft_free_tree(bash->root);
	bash->root = NULL;
	free_to_restart(bash);
}
