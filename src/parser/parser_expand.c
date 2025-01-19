/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:46:17 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/01/19 17:58:45 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	expandtokens(t_minishell *bash)
{
	t_token *aux;
	t_envp	*aux_envp;

	aux = bash->token;
	aux_envp = bash->envp;
	while(aux)
	{
		if (aux->type == EXP_EXIT)
//			expand_exit();
			return;
		else
		{
			if (aux->type == EXP_ENVP)
				expand_var(&aux, aux_envp);
			else
			{
				if (aux->type == WORD && aux->status == DOUBLE_Q)
					expand_in_dq(&aux, aux_envp);
				else
					aux = aux->next;
			}
		}
	}
}
/* void	expand_exitcode()
{
	return;
}
 */
void	expand_var(t_token **aux, t_envp *aux_envp)
{
	char	*env_var;
	char	*exp_var;
	t_token	*aux_prev;

	env_var = envp_name((*aux)->next->name);
	exp_var = ft_getenv(aux_envp, env_var);
	joinexpand(aux, env_var, exp_var);
	if ((*aux)->prev != NULL && (*aux)->prev->type == WORD)
	{
		aux_prev = (*aux)->prev;
		(*aux)->name = ft_strjoin(aux_prev->name, (*aux)->name);
		(*aux)->prev = aux_prev->prev;
		if (aux_prev->prev != NULL)
			aux_prev->prev->next = (*aux);
		free(aux_prev);
	}
	joinlast(aux);
}

void	expand_in_dq(t_token **aux, t_envp *aux_envp)
{
	char	*b_var;
	char	*a_var;
	char	*env_var;
	char	*exp_var;

	b_var = NULL;
	a_var = NULL;
	if (check_dollar((*aux)->name, &b_var, &a_var) == 0)
	{
		(*aux) = (*aux)->next;
		free(b_var);
		free(a_var);
		return;
	}
	env_var = envp_name(a_var);
	exp_var = ft_getenv(aux_envp, env_var);
	a_var = ft_substr(a_var, (ft_strlen(env_var)), (ft_strlen(a_var)-1));
	if ((*aux)->next->type == WORD)
		a_var = ft_strjoin(a_var, (*aux)->next->name);
	joinexpand_dq(aux, a_var, b_var, exp_var);
	joinlast(aux);
 	free(b_var);
	free(a_var);
}
