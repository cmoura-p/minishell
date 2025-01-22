/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brendon <brendon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 19:52:48 by brendon           #+#    #+#             */
/*   Updated: 2025/01/22 01:37:19 by brendon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_envadd(t_envp **env, t_envp *new)
{
	t_envp	*tmp;

	if (!*env)
	{
		*env = new;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

void	ft_env(t_minishell *minishell, char **args)
{
	t_envp	*tmp;

	if (args && args[0] && args[0][0])
	{
		if (args[0][0] == '-')
			ft_printf("bash: env: %s: invalid option\n", args[0]);
		else
			ft_printf("bash: env: %s: No such file or directory\n", args[1]);
		return ;
	}
	tmp = minishell->envp;
	if (!tmp)
		ft_printf("bash: env: No such file or directory\n");
	else
	{
		while (tmp)
		{
			ft_printf("%s=%s\n", tmp->name, tmp->content);
			tmp = tmp->next;
		}
	}
}
