/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:44:40 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/01/25 18:58:49 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_free_exec(t_exec *cmd)
{
	int	i;

	if (!cmd)
		return ;
	i = 0;
	while (cmd->args && cmd->args[i])
		free(cmd->args[i++]);
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
		return(ft_free_pipe((t_pipe *)root));
	else if (((t_redir *)root)->type == REDIR_IN
		|| ((t_redir *)root)->type == REDIR_OUT
		|| ((t_redir *)root)->type == REDIR_APP)
		return(ft_free_redir((t_redir *)root));
	else if (((t_exec *)root)->type == COMMAND)
		return(ft_free_exec((t_exec *)root));
}


void	free_to_restart(t_minishell *bash)
{
	t_token	*aux;

	if(!bash->token)
		return ;
	while (bash->token)
	{
		aux = bash->token;
		bash->token = bash->token->next;
		if (aux->name)
			{
				free(aux->name);
				aux->name = NULL;
			}
		if (aux)
			free(aux);
	}
	bash->token = NULL;
}

void	free_to_quit(t_minishell *bash, char *prompt)
{
	if (prompt)
		free(prompt);
	free_bash(bash);
	rl_clear_history();
	ft_printf("%s", SUCCESS_EXIT);
	exit(EXIT_SUCCESS);
}

void	free_bash(t_minishell *bash)
{
	free_envp(bash);
	free(bash);
}

void	free_envp(t_minishell *bash)
{
	t_envp	*aux;

	while (bash->envp)
	{
		aux = bash->envp;
		bash->envp = bash->envp->next;
		if (aux->name)
		{
			free(aux->name);
			aux->name = NULL;
		}
		if (aux->content)
		{
			free(aux->content);
			aux->content = NULL;
		}
		if (aux)
			free(aux);
	}
	bash->envp = NULL;
}
