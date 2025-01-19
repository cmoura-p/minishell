/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 09:26:41 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/01/18 23:45:05 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_tokenlst_back(t_token **newtoken, t_token *lst)
{
	while (lst->next)
		lst = lst->next;
	lst->next = *newtoken;
	(*newtoken)->i = lst->i + 1;
	(*newtoken)->prev = lst;
}

void	add_tokenlst(t_minishell **bash, char *name, \
			enum e_type type, enum e_status status_q)
{
	t_token	*newtoken;
	t_token	*aux;

	newtoken = (t_token *)malloc(sizeof(t_token));
	if (!newtoken)
		return ;
	newtoken->name = name;
	newtoken->type = type;
	newtoken->status = status_q;
	if (!(*bash)->token)
	{
		(*bash)->token = newtoken;
		(*bash)->token->i = 0;
		(*bash)->token->prev = NULL;
	}
	else
	{
		aux = (*bash)->token;
		add_tokenlst_back(&newtoken, aux);
	}
	newtoken->next = NULL;
}
int	ft_isword(char s)
{
	if ((s >= 9 && s <= 13) || s == 32
		|| s == '\'' || s == '"'
		|| s == '|' || s == '$' || s == '>'
		|| s == '<')
		return (0);
	return (1);
}

