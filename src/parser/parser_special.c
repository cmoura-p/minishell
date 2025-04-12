/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_special.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@students.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 00:10:04 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/04/12 14:07:16 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	blank_in_expand(t_token **token, char **exp_pieces, t_minishell *bash)
{
	t_token	*newtoken;
	int		flag;
	char	*after;
	char	*before;

	after = NULL;
	before = NULL;
	flag = 0;
	if (is_export((*token)))
		return ;
	while (ft_more_space(*exp_pieces))
	{
		if (after)
			free(after);
		if (split_string(*exp_pieces, &before, &after, ' '))
		{
			special_before(&newtoken, before, flag);
			free(*exp_pieces);
			(*exp_pieces) = ft_strdup(after);
		}
		flag = 1;
	}
	if (flag)
		special_final(&newtoken, after, &(*token), bash);
	return ;
}

void	special_before(t_token **newtoken, char *before, int flag)
{
	t_token	*tokenaux;

	tokenaux = (*newtoken);
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
		(*newtoken)->prev = tokenaux;
		tokenaux->next = (*newtoken);
	}
	tokenaux = (*newtoken);
	*newtoken = ft_calloc(1, sizeof(t_token));
	if (!*newtoken)
		return ;
	(*newtoken)->name = ft_strdup(" ");
	(*newtoken)->type = BLANK;
	(*newtoken)->status = NO_QUOTE;
	(*newtoken)->prev = tokenaux;
	tokenaux->next = (*newtoken);
}

void	special_last(t_token **newtoken, char *after)
{
	t_token	*tokenaux;

	tokenaux = (*newtoken);
	*newtoken = ft_calloc(1, sizeof(t_token));
	if (!*newtoken)
		return ;
	(*newtoken)->name = after;
	(*newtoken)->type = WORD;
	(*newtoken)->status = NO_QUOTE;
	(*newtoken)->prev = tokenaux;
	(*newtoken)->next = tokenaux->next;
	if (tokenaux->next)
		tokenaux->next->prev = (*newtoken);
	tokenaux->next = (*newtoken);
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
	free_token(*token);
	(*token) = NULL;
	free_token(auxtoken);
	auxtoken = NULL;
}

void	special_final(t_token **newtoken, char *after, t_token **token, \
		t_minishell *bash)
{
	special_last(&(*newtoken), after);
	special_clean(&(*token), &(*newtoken), bash);
	(*token) = (*newtoken);
}
