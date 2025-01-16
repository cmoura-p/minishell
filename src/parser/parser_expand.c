/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:46:17 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/01/16 00:22:36 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	valid_envp_char(char s, int i)
{
	if (i == 0 && (s >= '0' && s <= '9'))
		return (0);
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
		if (valid_envp_char(name[i], i))
			i++;
		else
			break;
	}
	str = ft_substr(name, 0, i);
	return (str);
}

char	*ft_getenv(t_minishell *bash, char *var)
{
	t_envp	*aux;

	aux = bash->envp;
	while (aux)
	{
		if (ft_strcmp(aux->name, var) == 0)
			return (aux->content);
		aux = aux->next;
	}
	return (NULL);
}

void	expandtokens(t_minishell *bash)
{
	t_token *aux;
	char	*env_var;
	char	*exp_var;

	aux = bash->token;
	while(aux)
	{
		if (aux->type == EXP_ENVP || aux->type == EXP_EXIT)
		{
			if (aux->type == EXP_EXIT)
				env_var = "?";			// aqui tenho que executar um join exit_code
			else
				env_var = envp_name(aux->next->name);
			exp_var = ft_getenv(bash, env_var);
			if (exp_var == NULL)
			{
				aux->next->type = ARGUMENT;
				joinnext(&aux, exp_var);
			}
			else
				joinexpand(&aux, env_var, exp_var);
		}
		else
			aux = aux->next;
	}
}
void joinexpand(t_token **token, char *name, char *name_exp)
{
	t_token	*aux;
	t_token	*aux_next;
	char	*sobra;			// $	USER[bla	cmoura-p

	aux = (*token);
	sobra = ft_substr((aux->next->name), (ft_strlen(name)), \
				(ft_strlen(aux->next->name)-1));
	aux->name = ft_strjoin(name_exp, sobra);
	aux_next = aux->next;
	aux->status = aux_next->status;
	aux->type = ARGUMENT;
	aux->next = aux_next->next;
	if (aux_next->next != NULL)
		aux_next->next->prev = aux_next->prev;
	free(aux_next);
	while ((aux->next != NULL) && (aux->next->type == BLANK)
		&& aux->next->next->type == WORD)
	{
		aux = aux->next->next;
		aux->type = ARGUMENT;
	}
}
