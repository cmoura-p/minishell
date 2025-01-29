/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brendon <brendon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 19:52:48 by brendon           #+#    #+#             */
/*   Updated: 2025/01/22 01:37:19 by brendon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_envadd(t_envp **env, t_envp *new)
{
	t_envp	*tmp;

	// Verifica se os parâmetros são válidos
	if (!env || !new || !new->name)
		return ;

	// Caso a lista esteja vazia, adiciona o novo nó
	if (!*env)
	{
		*env = new;
		return ;
	}

	tmp = *env;

	// Percorre a lista para verificar duplicatas
	while (tmp)
	{
		// Se o nome da variável já existir, atualiza o valor
		if (ft_strcmp(tmp->name, new->name) == 0)
		{
			free(tmp->content); // Libera o valor anterior
			if (new->content)
				tmp->content = ft_strdup(new->content);
			else
				tmp->content = NULL;
			free(new->name); // Libera o nome do novo nó
			free(new);       // Libera o novo nó
			return ;
		}

		// Avança para o próximo nó
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}

	// Adiciona o novo nó no final da lista
	tmp->next = new;
	new->prev = tmp;
}


void	ft_env(t_minishell *minishell, char **args)
{
	t_envp	*tmp;

	if (args && args[0] && args[0][0])
	{
		if (args[0][0] == '-')
			ft_printf("bash: env: %s: invalid option\n", args[0]);
		else
			ft_printf("bash: env: %s: No such file or directory\n", args[1]);
		return ;
	}
	tmp = minishell->envp;
	if (!tmp)
		ft_printf("bash: env: No such file or directory\n");
	else
	{
		while (tmp)
		{
			ft_printf("%s=%s\n", tmp->name, tmp->content);
			tmp = tmp->next;
		}
	}
}
