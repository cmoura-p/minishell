/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 23:00:17 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/02/12 13:16:54 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	run(t_minishell *bash)
{
	tokenizer(bash);
	print_token_list(bash->token);
	parsing(bash);

//	quando voltamos do parsing com um heredoc cancelado por ctrl+c
//	Nao precisamos do print_token_list
//	preciso limpar os heredocs e continuar o processo
//	na verdade  shell mata tudo quando tem um ctrl+c em heredoc
//	nao ha mais comandos na linha
    print_token_list(bash->token);
	free_to_restart(bash);
}
