/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: breda-si <breda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 23:38:51 by brendon           #+#    #+#             */
/*   Updated: 2025/03/04 23:40:29 by breda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_execute(t_minishell *minishell, void *root)
{
	if (!root)
		return ;
	if (((t_pipe *)root)->type == PIPE)
		ft_exec_pipe(minishell, (t_pipe *)root);
	else if (((t_redir *)root)->type == REDIR_IN
		|| ((t_redir *)root)->type == REDIR_OUT
		|| ((t_redir *)root)->type == REDIR_APP)
		ft_exec_redir(minishell, (t_redir *)root);
	else if (((t_exec *)root)->type == COMMAND)
		ft_exec_cmd(minishell, (t_exec *)root);
}
