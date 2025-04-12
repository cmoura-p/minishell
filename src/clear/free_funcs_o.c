/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_funcs_o.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@students.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 19:19:07 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/04/12 11:07:49 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_token(t_token *token)
{
	if (!token)
		return ;
	if (token->name)
	{
		free(token->name);
		token->name = NULL;
	}
	if (token->env_null)
	{
		free(token->env_null);
		token->env_null = NULL;
	}
	free(token);
	token = NULL;
}

void	ft_free_split(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		args[i] = NULL;
		i++;
	}
	free(args);
}

void	*free_null_redir(t_token *aux)
{
	if (aux->next)
		free_token(aux->next);
	if (aux)
		free_token(aux);
	return (NULL);
}
