/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_expo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brendon <brendon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:08:25 by brendon           #+#    #+#             */
/*   Updated: 2025/01/20 23:48:09 by brendon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	ft_insert_at_start(t_envp **export, t_envp *new)
{
	if (!*export || ft_strcmp((*export)->name, new->name) > 0)
	{
		new->next = *export;
		*export = new;
		return (1);
	}
	return (0);
}

static int	ft_replace_if_exists(t_envp *tmp, t_envp *new)
{
	if (ft_strcmp(tmp->name, new->name) == 0)
	{
		free(tmp->content);
		if (new->content)
			tmp->content = ft_strdup(new->content);
		else
			tmp->content = NULL;
		ft_freeexponode(new);
		return (1);
	}
	return (0);
}

void	ft_expoinsert(t_envp **export, t_envp *new)
{
	t_envp	*tmp;
	t_envp	*prev;

	if (!new || ft_insert_at_start(export, new))
		return ;
	tmp = *export;
	prev = NULL;
	while (tmp && ft_strcmp(tmp->name, new->name) < 0)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp && ft_replace_if_exists(tmp, new))
		return ;
	new->next = tmp;
	if (prev)
		prev->next = new;
}
