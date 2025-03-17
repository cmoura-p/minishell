/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@students.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 23:00:17 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/03/17 08:57:53 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	run(t_minishell *bash)
{
	t_token	*aux;

	tokenizer(bash);
	ft_printf("Tokenizacao \n");
	print_token_list(bash->token);
    parsing(bash);
	if (!bash->token)
		return ;
	init_signals();
	aux = bash->token;
	//if (bash->token->name[0] == '\0')
	//	aux = bash->token->next;
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
