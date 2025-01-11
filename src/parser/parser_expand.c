/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:46:17 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/01/11 11:49:58 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	valid_envp_char(char s)
{
	if ((s >= '0' && s <= '9') || (s >= 65 && s <= 90)
		|| (s >= 97 && s <= 122) || s == '_')
		return (1);
	return (0);
}

char	*envp_name(char *name)
{
	char	*str;
	int		i;

	i = 0;
	while (name[i])
	{
		if (valid_envp_char(name[i]))
			i++;
		else
			break;
	}
	str = ft_substr(name, 0, i);
	return (str);
}

void	expandwords(t_minishell *bash)
{
	t_token *aux;
	char	*env_var;

	aux = bash->token;
	while(aux)
	{
		if (aux->type == EXP_ENVP)
		{
			env_var = envp_name(aux->next->name);
			// getenv
			joinnext(&aux, env_var);
		}
		aux = aux->next;
	}
}
// do Murilo
/*
char	*ft_getenv(t_list *envp_lst, char *name)
{
	t_var	*var;
	t_list	*lst;

	lst = envp_lst;
	while (lst)
	{
		var = (t_var *)lst->content;
		if (ft_strcmp(var->name, name) == 0)
			return (var->value);
		lst = lst->next;
	}
	return (NULL);
}
 */
