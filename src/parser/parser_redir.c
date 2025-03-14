/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@students.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:19:54 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/03/13 16:15:18 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_redir(t_minishell *bash)
{
	t_token	*aux;

	aux = bash->token;
	while (aux)
	{
		if (aux->type == REDIR_IN)
			aux = set_redir_file(aux, FILE_IN);
		else if (aux->type == REDIR_OUT)
			aux = set_redir_file(aux, FILE_OUT);
		else if (aux->type == REDIR_APP)
			aux = set_redir_file(aux, FILE_APP);
		else
			aux = aux->next;
	}
}

t_token	*set_redir_file(t_token *token, enum e_type type)
{
	token = token->next;
	if (!token)					// AQUI
		return (token);			// AQUI
	if (token->type == BLANK || token->type == PIPE)
		token = token->next;
	while (token && token->type == WORD)
	{
		token->type = type;
		token = token->next;
	}
	return (token);
}
char	*envp_trimmed(const char *str)
{
	char	*cleaned;
	int		i;
	int		j;

	i = 0;
	j = 0;
	cleaned = (char *)malloc(sizeof(char) * (strlen(str) + 1));
	if (!cleaned)
		return (NULL);
	while (str[i])
	{
		if (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
			i++;
		else
		{
			while (str[i] && ((str[i] < 9 || str[i] > 13) && str[i] != ' '))
				cleaned[j++] = str[i++];
			if (str[i])
				cleaned[j++] = ' ';
		}
	}
	cleaned[j] = '\0';
	return (cleaned);
}

void	check_exp_null(t_token *aux, char *exp_var, char *env_var)
{
	if (*exp_var == '\0')
	{
		free(aux->env_null);
		aux->env_null = ft_strjoin("$", env_var);
	}
}
