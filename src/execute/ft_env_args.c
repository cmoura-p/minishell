/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: breda-si <breda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 23:37:16 by brendon           #+#    #+#             */
/*   Updated: 2025/03/10 10:43:29 by breda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strjoin_c(char c, char *s1, char *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = (char *)malloc(len1 + len2 + 2);
	if (!result)
		return (NULL);
	ft_strcpy(result, s1);
	result[len1] = c;
	ft_strcpy(result + len1 + 1, s2);
	return (result);
}

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
		args[i] = ft_strjoin_c('=', tmp->name, tmp->content);
		if (!args[i])
		{
			while (i > 0)
				free(args[--i]);
			free(args);
			return (NULL);
		}
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
