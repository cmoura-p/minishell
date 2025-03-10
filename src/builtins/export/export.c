/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: breda-si <breda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:40:41 by brendon           #+#    #+#             */
/*   Updated: 2025/03/10 09:57:25 by breda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_envp	*ft_exponew(char *name, char *value)
{
	t_envp	*new;

	new = malloc(sizeof(t_envp));
	if (!new)
		return (NULL);
	new->name = ft_strdup(name);
	if (value)
		new->content = ft_strdup(value);
	else
		new->content = NULL;
	new->next = NULL;
	return (new);
}

void	ft_export_print(t_envp *export)
{
	while (export)
	{
		if (export->content)
			ft_printf("declare -x %s=\"%s\"\n", export->name, export->content);
		else
			ft_printf("declare -x %s\n", export->name);
		export = export->next;
	}
}

int	ft_validarg(char *arg, t_minishell *minishell)
{
	int	i;

	i = -1;
	if (!(ft_isalpha(arg[0]) || arg[0] == '_'))
	{
		ft_fprintf(STDERR_FILENO,
			"minishell: export: `%s': not a valid identifier\n", arg);
		minishell->exit_status = 1;
		return (0);
	}
	while (arg[++i] && arg[i] != '=')
	{
		if (!(ft_isalnum(arg[i]) || arg[i] == '_' || arg[i] == '='))
		{
			ft_fprintf(STDERR_FILENO,
				"minishell: export: `%s': not a valid identifier\n", arg);
			minishell->exit_status = 1;
			return (0);
		}
	}
	return (1);
}

void	ft_expoenvatt(t_minishell *minishell, char **args)
{
	int	i;
	int	j;

	i = -1;
	minishell->exit_status = 0;
	while (args[++i] != NULL && args[i])
	{
		if (!ft_validarg(args[i], minishell))
			continue ;
		j = 0;
		while (args[i][j] && args[i][j] != '=')
			j++;
		if (args[i][j] == '=')
		{
			args[i][j] = '\0';
			ft_expoinsert(&minishell->export,
				ft_exponew(args[i], &args[i][j + 1]));
			ft_envadd(&minishell->envp,
				ft_exponew(args[i], &args[i][j + 1]));
		}
		else
			ft_expoinsert(&minishell->export, ft_exponew(args[i], NULL));
	}
}

void	ft_export(t_minishell *minishell, char **args)
{
	if (!args || !args[0] || !args[0][0])
		ft_export_print(minishell->export);
	else
		ft_expoenvatt(minishell, args);
}
