/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:58:23 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/01/25 19:47:17 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parsing(t_minishell *bash)
{
	expandtokens(bash);
//	print_token_list(bash->token);
	jointokens(bash);
	set_commands(bash);
//	print_token_list(bash->token);
	remove_blank(bash);
//	print_token_list(bash->token);
	set_arguments(bash);
	set_redir(bash);
	print_token_list(bash->token);
}
