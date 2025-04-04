/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_special.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@students.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 00:10:04 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/04/04 02:02:30 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	blank_in_expand(t_token **token, char *exp_pieces, \
	char	*before, char *after, t_minishell *bash)
{
	t_token	*newtoken;
	t_token	*tokenaux;
	int		flag;

	flag = 0;
	tokenaux = NULL;
	if (is_export((*token)))
		return (flag);
	while (ft_more_space(exp_pieces))
	{
		if (split_string(exp_pieces, &before, &after, ' '))
		{
			special_before(&tokenaux, &newtoken, before, flag);
			ft_strcpy(exp_pieces, after);
		}
		tokenaux = newtoken;
		flag = 1;
	}
	if (flag)
	{
		special_last(&tokenaux, &newtoken, after);
		special_clean(&(*token), &newtoken, bash);
		(*token) = newtoken;
	}
	return (flag);
}

void	special_before(t_token **token, t_token **newtoken, char *before, int flag)
{
	t_token *newaux;

	*newtoken = ft_calloc(1, sizeof(t_token));
	if (!*newtoken)
		return ;
	(*newtoken)->name = before;
	(*newtoken)->type = WORD;
	(*newtoken)->status = NO_QUOTE;
	(*newtoken)->prev = NULL;
	(*newtoken)->next = NULL;
	if (flag == 1)
	{
		(*newtoken)->prev = (*token);
		(*token)->next = (*newtoken);
	}
	newaux = (*newtoken);
	*newtoken = ft_calloc(1, sizeof(t_token));
	if (!*newtoken)
		return ;
	(*newtoken)->name = ft_strdup(" ");
	(*newtoken)->type = BLANK;
	(*newtoken)->status = NO_QUOTE;
	(*newtoken)->prev = newaux;
	newaux->next = (*newtoken);
}

void	special_last(t_token **token, t_token **newtoken, char *after)
{
	*newtoken = ft_calloc(1, sizeof(t_token));
	if (!*newtoken)
		return ;
	(*newtoken)->name = after;
	(*newtoken)->type = WORD;
	(*newtoken)->status = NO_QUOTE;
	(*newtoken)->prev = (*token);
	(*newtoken)->next = (*token)->next;
	if ((*token)->next)
		(*token)->next->prev = (*newtoken);
	(*token)->next = (*newtoken);
}

void	special_clean(t_token **token, t_token **newtoken, t_minishell *bash)
{
	t_token	*auxtoken;

	(*newtoken)->next = (*token)->next->next;
	while ((*newtoken)->prev)
		(*newtoken) = (*newtoken)->prev;
	(*newtoken)->prev = (*token)->prev;
	if ((*token)->prev)
		(*token)->prev->next = (*newtoken);
	else
		bash->token = (*newtoken);
	auxtoken = (*token)->next;
	free_token(* token);
	(*token) = NULL;
	free_token(auxtoken);
	auxtoken = NULL;
}
