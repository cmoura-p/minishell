/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brendon <brendon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 19:52:48 by brendon           #+#    #+#             */
/*   Updated: 2025/01/14 17:13:31 by brendon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_envadd(t_env **env, char *var, char *valor)
{
	t_env	*new;
	t_env	*tmp;

	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->var = ft_strdup(var);
	new->valor = ft_strdup(valor);
	new->next = NULL;
	if (!*env)
	{
		*env = new;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	ft_env(t_minishell *minishell)
{
	t_env	*tmp;

	tmp = minishell->v_env;
	if (!tmp)
		printf("bash: env: No such file or directory\n");
	else
	{
		while (tmp)
		{
			printf("%s=%s\n", tmp->var, tmp->valor);
			tmp = tmp->next;
		}
	}
}
