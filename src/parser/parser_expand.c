/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@students.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:46:17 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/03/01 21:14:13 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	expandtokens(t_minishell *bash)
{
	t_token	*aux;
	t_envp	*aux_envp;

	aux = bash->token;
	aux_envp = bash->envp;
	while (aux)
	{
		if (aux->type == EXP_EXIT)
//			expand_exit();
			return ;
		else
		{
			if ((aux->type == EXP_ENVP) && (checked_for_hd(aux) == 0))
				expand_var(&aux, aux_envp);
			else
			{
				if ((aux->type == WORD && aux->status == DOUBLE_Q)
					&& (checked_for_hd(aux) == 0))
					expand_in_dq(bash, &aux);
				else
					aux = aux->next;
			}
		}
	}
}
/* void	expand_exit()
{
	return;
}
*/

void	expand_var(t_token **aux, t_envp *aux_envp)
{
	char	*env_var;
	char	*exp_var;
	char	*newname;

	if (!(*aux)->next)
		return ;
	env_var = envp_name((*aux)->next->name);
	if (*env_var == '\0')
	{
		free(env_var);
		(*aux) = (*aux)->next;
		return ;
	}
	exp_var = ft_getenv(aux_envp, env_var);
	if (!blank_in_expand((*aux), exp_var))
		joinexpand(aux, env_var, exp_var);
	if (((*aux)->prev != NULL) && ((*aux)->prev->type == WORD))
	{
		newname = ft_strjoin((*aux)->prev->name, (*aux)->name);
		joinprev(aux, newname);
	}
	free(env_var);
}

void	expand_in_dq(t_minishell *bash, t_token **aux)
{
	char	*b_var;
	char	*a_var;

	b_var = NULL;
	a_var = NULL;
	if (split_string((*aux)->name, &b_var, &a_var, '$') == 0)
	{
		(*aux) = (*aux)->next;
		return ;
	}
	if (b_var && *b_var != '\0')
		add_tokenlst_dq(bash, aux, b_var, WORD, NO_QUOTE);
	if (a_var && a_var[0] == '?')
	{
		add_tokenlst_dq(bash, aux, ft_strdup("$?"), EXP_EXIT, NO_QUOTE);
//	problema
		a_var = ft_substr(a_var, 1, ft_strlen(a_var) - 1);
	}
	else
		add_tokenlst_dq(bash, aux, ft_strdup("$"), EXP_ENVP, NO_QUOTE);
	if (a_var && *a_var != '\0')
		newtoken_after_parsing(aux, a_var);
	else
		del_tokenlst(bash, aux);
	free(a_var);
	free(b_var);
}

void	newtoken_after_parsing(t_token **aux, char *a_var)
{
	char	*env_var;

	(*aux)->type = WORD;
	(*aux)->status = SINGLE_Q;
	ft_strcpy((*aux)->name, a_var);
	env_var = envp_name(a_var);
	if (*env_var != '\0')
	{
		ft_strcpy((*aux)->name, env_var);
		get_sobra(aux, a_var, env_var);
	}
	else
		(*aux)->prev->type = WORD;
	free(env_var);
	(*aux) = (*aux)->prev;
}
