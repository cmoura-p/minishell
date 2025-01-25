/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 21:17:10 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/01/24 21:20:56 by cmoura-p         ###   ########.fr       */
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

char	*ft_getenv(t_envp *aux, char *var)
{
	while (aux)
	{
		if (ft_strcmp(aux->name, var) == 0)
			return (aux->content);
		aux = aux->next;
	}
	return (NULL);
}

int check_dollar(char *line, char **before, char **after)
{
	char *dollar_sign;
	size_t before_len;

	if (!line)
		return (0);
	dollar_sign = ft_strchr(line, '$');
	if (!dollar_sign)
		return (0);
	else
	{
		before_len = dollar_sign - line;
		*before = malloc(before_len + 1);
		if (!*before)
			return (0);
		ft_strlcpy(*before, line, before_len + 1);
		(*before)[before_len] = '\0';
		*after = ft_strdup(dollar_sign + 1);
		if (!*after)
		{
			free(*before);
			return (0);
		}
	}
	return 1;
}
/* void	joinlast(t_token **aux)
{
	while (((*aux)->next != NULL) && ((*aux)->next->type == BLANK)
		&& (*aux)->next->next->type == WORD)
	{
		*aux = (*aux)->next->next;
		(*aux)->type = ARGUMENT;
	}
} */
