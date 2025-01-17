/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brendon <brendon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:46:35 by brendon           #+#    #+#             */
/*   Updated: 2025/01/14 22:29:12 by brendon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_search_del(t_env **env, char *key)
{
	t_list	*tmp;
	t_list	*prev;

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
			free(tmp->value);
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
	int	j;

	i = 0;
	if (!args[1])
		return ;
	if (args[i][0] == '-')
	{
		printf("minishell: unset: %s: invalid option\n", args[i]);
		return ;
	}
	while (args[i])
	{
		ft_search_del(minishell->env, args[i]);
		ft_search_del(minishell->expo, args[i]);
		i++;
	}
}
