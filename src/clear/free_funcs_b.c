/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_funcs_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: breda-si <breda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 19:14:03 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/03/10 23:18:58 by breda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
}

void	ft_free_exec(t_exec *cmd)
{
	int	i;

	if (!cmd || !cmd->args)
		return ;
	i = 0;
	while (cmd->args && cmd->args[i])
	{
		if(cmd->args[i])
			free(cmd->args[i++]);
	}
	free(cmd->args);
	free(cmd);
}

void	ft_free_redir(t_redir *redir)
{
	if (!redir)
		return ;
	if (redir->file_name)
		free(redir->file_name);
	if (redir->next)
		ft_free_tree(redir->next);
	free(redir);
}

void	ft_free_pipe(t_pipe *pipe)
{
	if (!pipe)
		return ;
	if (pipe->left)
		ft_free_tree(pipe->left);
	if (pipe->right)
		ft_free_tree(pipe->right);
	free(pipe);
}

void	ft_free_tree(void *root)
{
	if (!root)
		return ;
	if (((t_pipe *)root)->type == PIPE)
		return (ft_free_pipe((t_pipe *)root));
	else if (((t_redir *)root)->type == REDIR_IN
		|| ((t_redir *)root)->type == REDIR_OUT
		|| ((t_redir *)root)->type == REDIR_APP)
		return (ft_free_redir((t_redir *)root));
	else if (((t_exec *)root)->type == COMMAND)
		return (ft_free_exec((t_exec *)root));
}
