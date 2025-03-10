/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_funcs_c.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@students.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:44:40 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/03/10 18:35:59 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
		aux = NULL;
	}
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

void	free_to_quit(t_minishell *bash)
{
	free_bash(bash);
	rl_clear_history();
	ft_printf("%s", SUCCESS_EXIT);
	exit(EXIT_SUCCESS);
}

void	free_bash(t_minishell *bash)
{
	if (bash->cmd_line)
		free(bash->cmd_line);
	if (bash->envp)
		free_envp(bash);
	if (bash->export)
		free_expo(bash);
	if (bash->token)
		clean_tokens(bash);
	if (bash->heredoc)
		clean_heredoc(bash);
	free(bash);
}
