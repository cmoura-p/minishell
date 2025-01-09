/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brendon <brendon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 19:52:48 by brendon           #+#    #+#             */
/*   Updated: 2025/01/08 10:19:54 by brendon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_env(t_minishell *minishell)
{
	t_env	*tmp;

	tmp = minishell->v_env;
	if (!tmp)
		printf("bash: env: No such file or directory\n");
	else
	{
		while (tmp)
		{
			printf("%s=%s\n", tmp->var, tmp->valor);
			tmp = tmp->next;
		}
	}
}
