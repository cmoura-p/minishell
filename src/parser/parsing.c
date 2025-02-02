/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:58:23 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/01/30 19:43:10 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parsing(t_minishell *bash)
{
	expandtokens(bash);
	jointokens(bash);
	set_redir(bash);
//	print_token_list(bash->token);
	set_commands(bash);
	remove_blank(bash);
//	print_token_list(bash->token);
	set_arguments(bash);
	if (bash->heredoc)
	{
//		organizar sinais para heredoc
		heredoc(bash);
//		retornar os sinais inciais
	}
	print_token_list(bash->token);
}
