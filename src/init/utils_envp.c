/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@students.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 21:34:51 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/02/12 16:00:05 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	load_envp(t_minishell *bash, char **envp)
{
	int		i;
	char	*name;
	char	*content;

	i = 0;
	name = NULL;
	content = NULL;
	if (!envp)
		return ;
	while (envp[i])
	{
		if (!split_envp(envp[i], &name, &content))
			return ;
		add_envplst(bash, name, content);
		i++;
	}
}

void	add_envplst(t_minishell *bash, char *name, char *content)
{
	t_envp	*newenvp;
	t_envp	*aux;

	newenvp = (t_envp *)malloc(sizeof(t_envp));
	if (!newenvp)
		return ;
	newenvp->name = name;
	newenvp->content = content;
	newenvp->next = NULL;
	newenvp->prev = NULL;
	if (!bash->envp)
		bash->envp = newenvp;
	else
	{
		aux = bash->envp;
		add_envplst_back(&newenvp, aux);
	}
}

void	add_envplst_back(t_envp **newenvp, t_envp *lst)
{
	while (lst->next)
		lst = lst->next;
	lst->next = *newenvp;
	(*newenvp)->prev = lst;
}

int	split_envp(const char *envp_line, char **before, char **after)
{
	char	*equal_sign;
	size_t	before_len;

	if (!envp_line)
		return (0);
	equal_sign = ft_strchr(envp_line, '=');
	if (!equal_sign)
	{
		*before = ft_strdup(envp_line);
		*after = NULL;
		return (1);
	}
	before_len = equal_sign - envp_line;
	*before = malloc(before_len + 1);
	if (!*before)
		return (0);
	ft_strlcpy(*before, envp_line, before_len + 1);
	(*before)[before_len] = '\0';
	*after = ft_strdup(equal_sign + 1);
	if (!*after)
	{
		free(*before);
		return (0);
	}
	return (1);
}

void	free_envp(t_minishell *bash)
{
	t_envp	*aux;

	while (bash->envp)
	{
		aux = bash->envp;
		bash->envp = bash->envp->next;
		if (aux->name)
		{
			free(aux->name);
			aux->name = NULL;
		}
		if (aux->content)
		{
			free(aux->content);
			aux->content = NULL;
		}
		if (aux)
			free(aux);
	}
	bash->envp = NULL;
}
