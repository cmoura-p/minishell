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

void	ft_update_env_value(t_envp *existing, t_envp *new)
{
	free(existing->content);
	if (new->content)
		existing->content = ft_strdup(new->content);
	else
		existing->content = NULL;
}

t_envp	*ft_find_env(t_envp *env, char *name)
{
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
			return (env);
		if (!env->next)
			break ;
		env = env->next;
	}
	return (env);
}

void	ft_envadd(t_envp **env, t_envp *new)
{
	t_envp	*tmp;

	if (!env || !new || !new->name)
		return ;
	if (!*env)
		*env = new;
	else
	{
		tmp = ft_find_env(*env, new->name);
		if (tmp && ft_strcmp(tmp->name, new->name) == 0)
			ft_update_env_value(tmp, new);
		else
		{
			tmp->next = new;
			new->prev = tmp;
		}
	}
}



void	ft_env(t_minishell *minishell, char **args)
{
	t_envp	*tmp;

	if (args && args[0] && args[0][0])
	{
		if (args[0][0] == '-' && args[0][1])
			ft_printf("env: invalid option -- '%s'\n", &args[0][1]);
		else if (args[0][0] != '-')
			ft_printf("env: ‘%s’: No such file or directory\n", args[0]);
		else if (args[0][0] == '-' && args[1])
			ft_printf("env: ‘%s’: No such file or directory\n", args[1]);
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
