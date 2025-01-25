/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:46:17 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/01/24 22:34:38 by cmoura-p         ###   ########.fr       */
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
					expand_in_dq(bash, &aux);
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

	if (!(*aux)->next)
		return;
	env_var = envp_name((*aux)->next->name);
	exp_var = ft_getenv(aux_envp, env_var);
	joinexpand(aux, env_var, exp_var);
	if ((*aux)->prev != NULL && (*aux)->prev->type == WORD)
	{
		(*aux)->name = ft_strjoin((*aux)->prev->name, (*aux)->name);
		joinprev(aux, (*aux)->name);
	}
//	joinlast(aux);
}

void	expand_in_dq(t_minishell *bash, t_token **aux)
{
	char	*b_var;
	char	*a_var;

	b_var = NULL;
	a_var = NULL;
	// aqui a ideia eh fazer um loop enquanto tiver dentro das aspas duplas
	if (check_dollar((*aux)->name, &b_var, &a_var) == 0)
	{
		(*aux) = (*aux)->next;
		return;
	}
	if (b_var && *b_var != '\0')
		add_tokenlst_mid(bash, aux, b_var, WORD, NO_QUOTE);
	add_tokenlst_mid(bash, aux, "$", EXP_ENVP, NO_QUOTE);
	if (a_var && *a_var != '\0')
	{
//		aqui o a_var deveria ter apenas a parte valida do env
//		se tiver outro(s) $ tem de parar ai e essa string que ta sobrando
//		tem de ser um novo token word double
		(*aux)->name = envp_name(a_var);
		(*aux) = (*aux)->prev;
	}
	else
		del_tokenlst(bash, aux);
	expand_var(aux, bash->envp);
}
