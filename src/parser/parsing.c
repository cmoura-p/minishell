/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:58:23 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/02/20 14:37:14 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parsing(t_minishell *bash)
{
	expandtokens(bash);
	printf("pos expandtokens \n");
    print_token_list(bash->token);
	remove_exp_null(bash);
	jointokens(bash);
	printf("pos jointokens \n");
	print_token_list(bash->token);
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
	printf("pos tudo \n");
    print_token_list(bash->token);
}
