/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:44:40 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/02/25 19:29:50 by cmoura-p         ###   ########.fr       */
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
	if (bash->token)
		clean_tokens(bash);
	if (bash->heredoc)
		clean_heredoc(bash);
}
void	clean_tokens(t_minishell *bash)
{
	t_token	*aux;

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
void	clean_heredoc(t_minishell *bash)
{
	t_heredoc	*aux;

	while (bash->heredoc)
	{
		aux = bash->heredoc;
		bash->heredoc = bash->heredoc->next;
		if (aux->eo_heredoc)
		{
			free(aux->eo_heredoc);
			aux->eo_heredoc = NULL;
		}
		if (aux)
			free(aux);
	}
	bash->heredoc = NULL;
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
	if (bash->envp)
		free_envp(bash);
	if (bash->token)
		clean_tokens(bash);
	if (bash->heredoc)
		clean_heredoc(bash);
		// fazer o free das outras estruturas
	free(bash);
}
