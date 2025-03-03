/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@students.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 21:17:10 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/03/01 21:15:06 by cmoura-p         ###   ########.fr       */
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
			break ;
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
	return ("");
}

int	blank_in_expand(t_token *token, char *exp_var)
{
	char	*before;
	char	*after;
	t_token	*newtoken;

	before = NULL;
	after = NULL;
	if (split_string(exp_var, &before, &after, ' '))
	{
		token->name = before;
		token->type = WORD;
		newtoken = ft_calloc(1, sizeof(t_token));
		if (!newtoken)
			return (0);
		newtoken->name = ft_strdup(" ");
		newtoken->type = BLANK;
		newtoken->status = NO_QUOTE;
		newtoken->prev = token;
		newtoken->next = token->next;
		token->next->prev = newtoken;
		token->next = newtoken;
		newtoken->next->name = after;
		return (1);
	}
	return (0);
}

int	split_string(char *line, char **before, char **after, char c)
{
	char	*sign;
	size_t	before_len;

	if (!line)
		return (0);
	sign = ft_strchr(line, c);
	if (!sign)
		return (0);
	else
	{
		before_len = sign - line;
		*before = malloc(before_len + 1);
		if (!*before)
			return (0);
		ft_strlcpy(*before, line, before_len + 1);
		(*before)[before_len] = '\0';
		*after = ft_strdup(sign + 1);
		if (!*after)
		{
			free(*before);
			return (0);
		}
	}
	return (1);
}
