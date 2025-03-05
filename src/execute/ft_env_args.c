/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: breda-si <breda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 23:37:16 by brendon           #+#    #+#             */
/*   Updated: 2025/03/04 23:40:07 by breda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	int	count_envp(t_envp *envp)
{
	int		count;
	t_envp	*tmp;

	count = 0;
	tmp = envp;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

static	char	**allocate_args(t_envp *envp, int count)
{
	char	**args;
	int		i;
	t_envp	*tmp;

	args = (char **)malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	i = 0;
	tmp = envp;
	while (tmp)
	{
		args[i] = (char *)malloc(strlen(tmp->name) + strlen(tmp->content) + 2);
		if (!args[i])
		{
			while (i > 0)
				free(args[--i]);
			free(args);
			return (NULL);
		}
		sprintf(args[i], "%s=%s", tmp->name, tmp->content);
		i++;
		tmp = tmp->next;
	}
	args[i] = NULL;
	return (args);
}

char	**ft_env_args(t_envp *envp)
{
	int		count;
	char	**args;

	count = count_envp(envp);
	args = allocate_args(envp, count);
	return (args);
}
