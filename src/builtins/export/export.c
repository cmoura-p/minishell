/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brendon <brendon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:40:41 by brendon           #+#    #+#             */
/*   Updated: 2025/01/14 20:11:21 by brendon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_freeexponode(t_expo *node)
{
	free(node->name);
	free(node->value);
	free(node);
}

void	ft_exponew(t_expo **new, char *name, char *value)
{
	*new = malloc(sizeof(t_expo));
	if (!*new)
		return ;
	(*new)->name = ft_strdup(name);
	if (value)
		(*new)->value = ft_strdup(value);
	else
		(*new)->value = NULL;
	(*new)->next = NULL;
}

void	ft_export_print(t_expo *export)
{
	while (export)
	{
		if (export->value)
			ft_printf("declare -x %s=\"%s\"\n", export->name, export->value);
		else
			ft_printf("declare -x %s\n", export->name);
		export = export->next;
	}
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

void	ft_export(t_minishell *minishell, t_expo *export, char **args)
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
				ft_expoinsert(&export, ft_exponew(args[i], args[i][j + 1]));
				ft_envadd(minishell->env, ft_envnew(args[i], args[i][j + 1]));
			}
			else
				ft_expoinsert(&export, ft_exponew(args[i], NULL));
		}
	}
}
