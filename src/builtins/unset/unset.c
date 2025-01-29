/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brendon <brendon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:46:35 by brendon           #+#    #+#             */
/*   Updated: 2025/01/20 10:15:01 by brendon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_search_del(t_envp **env, char *key)
{
	t_envp	*tmp;
	t_envp	*prev;

	tmp = *env;
	prev = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, key) == 0)
		{
			if (prev)
				prev->next = tmp->next;
			else
				*env = tmp->next;
			free(tmp->name);
			free(tmp->content);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	ft_unset(t_minishell *minishell, char **args)
{
	int	i;

	i = 0;
	if (!args[0])
		return ;
	if (args[i][0] == '-')
	{
		printf("minishell: unset: %s: invalid option\n", args[i]);
		return ;
	}
	while (args[i])
	{
		ft_search_del(&minishell->envp, args[i]);
		ft_search_del(&minishell->export, args[i]);
		i++;
	}
}
