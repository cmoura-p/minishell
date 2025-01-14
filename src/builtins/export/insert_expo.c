/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_expo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brendon <brendon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:08:25 by brendon           #+#    #+#             */
/*   Updated: 2025/01/14 17:08:26 by brendon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Verifica se o nó novo deve ser inserido no início da lista
static int	ft_insert_at_start(t_expo **export, t_expo *new)
{
	if (!*export || ft_strcmp((*export)->name, new->name) > 0)
	{
		new->next = *export;
		*export = new;
		return (1);
	}
	return (0);
}

// Substitui o valor de um nó existente
static int	ft_replace_if_exists(t_expo *tmp, t_expo *new)
{
	if (ft_strcmp(tmp->name, new->name) == 0)
	{
		free(tmp->value);
		tmp->value = new->value ? ft_strdup(new->value) : NULL;
		ft_freeexponode(new);
		return (1);
	}
	return (0);
}

// Função principal
void	ft_expoinsert(t_expo **export, t_expo *new)
{
	t_expo	*tmp;
	t_expo	*prev;

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

	// Insere o novo nó na posição correta
	new->next = tmp;
	if (prev)
		prev->next = new;
}
