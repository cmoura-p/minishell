/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: breda-si <breda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 23:00:17 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/03/11 08:37:39 by breda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	run(t_minishell *bash)
{
	t_token	*aux;

	tokenizer(bash);
	print_token_list(bash->token);
	parsing(bash);
	print_token_list(bash->token);
	if (!bash->token)
		return ;
	init_signals();
	aux = bash->token;
	if (bash->token->name[0] == '\0')
		aux = bash->token->next;
	bash->root = ft_tree(duplicate_token_list(aux), bash);
	if (!bash->root)
	{
		free_to_restart(bash);
		return ;
	}
	ft_execute(bash, bash->root);
	ft_free_tree(bash->root);
	free_to_restart(bash);
}
