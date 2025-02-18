/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:58:23 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/02/18 23:14:02 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// verificar a expansao no parsing porque
// quando ha expansao entre ' ' nao eh expansao
// fica ruim quando por exemplo
// echo $USER'$USER'$user"$USER"
// eh asequencia de string e nulo

void	parsing(t_minishell *bash)
{
	expandtokens(bash);
    print_token_list(bash->token);
	jointokens(bash);
//	print_token_list(bash->token);
	set_redir(bash);
	set_commands(bash);
	remove_blank(bash);
	set_arguments(bash);
	if (bash->heredoc)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		heredoc(bash);
		init_signals();
	}
    print_token_list(bash->token);
}
