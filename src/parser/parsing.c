/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:58:23 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/02/10 23:49:38 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parsing(t_minishell *bash)
{
	expandtokens(bash);
//	print_token_list(bash->token);
	jointokens(bash);
	set_redir(bash);
	set_commands(bash);
	remove_blank(bash);
	set_arguments(bash);
	if (bash->heredoc)
	{
//		organizar sinais para heredoc
		heredoc(bash);
//		retornar os sinais inciais
	}
}
