/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brendon <brendon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:40:41 by brendon           #+#    #+#             */
/*   Updated: 2025/01/09 18:44:26 by brendon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_export_print(t_expo *export)
{
	t_expo	*tmp;

	tmp = export;
	while (tmp)
	{
		if (tmp->value)
			ft_printf("declare -x %s=\"%s\"\n", tmp->name, tmp->value);
		else
			ft_printf("declare -x %s\n", tmp->name);
		tmp = tmp->next;
	}
}

t_expo	*ft_exponew(char *name, char *value)
{
	t_expo	*new;

	new = malloc(sizeof(t_expo));
	if (!new)
		return (NULL);
	new->name = ft_strdup(name);
	if (!new->name)
	{
		free(new);
		return (NULL);
	}
	if (value)
	{
		new->value = ft_strdup(value);
		if (!new->value)
		{
			free(new->name);
			free(new);
			return (NULL);
		}
	}
	else
		new->value = NULL;
	new->next = NULL;
	return (new);
}

void	ft_expoadd_back(t_expo **lst, t_expo *new)
{
	t_expo	*tmp;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int	ft_validarg(char *arg)
{
	int	i;

	i = 0;
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
	{
		ft_printf("minishell: export: `%s': not a valid identifier\n", arg);
		return (0);
	}
	while (arg[++i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			ft_printf("minishell: export: `%s': not a valid identifier\n", arg);
			return (0);
		}
	}
	return (1);
}

void	ft_export(t_expo *export, char **args)
{
	int	i;
	int	j;

	i = 0;
	if (!args[1])
		ft_export_print(export);
	else
	{
		while (args[++i])
		{
			if (!ft_validarg(args[i]))
				continue ;
			j = 0;
			while (args[i][j] && args[i][j] != '=')
				j++;
			if (args[i][j] == '=')
			{
				args[i][j] = '\0';
				ft_expoadd_back(&export, ft_exponew(args[i], args[i][j + 1]));
			}
			else
				ft_expoadd_back(&export, ft_exponew(args[i], NULL));
		}
	}
}
