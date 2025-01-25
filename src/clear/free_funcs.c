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

void	free_to_restart(t_minishell *bash)
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
