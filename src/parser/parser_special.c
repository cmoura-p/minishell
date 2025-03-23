/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_special.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@students.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 00:10:04 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/03/23 09:28:43 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	blank_in_expand(t_token *token, char *exp_pieces, \
	char	*before, char *after)
{
	t_token	*newtoken;

	if (is_export(token))
		return (0);
	if (split_string(exp_pieces, &before, &after, ' '))
	{
		special_before(&token, &newtoken, before);
		if (newtoken->next && ft_more_space(after))
		{
			special_after(&newtoken, after);
			token = newtoken->next;
			exp_pieces = after;
			if (!blank_in_expand(token, exp_pieces, "", ""))
				return (1);
		}
		else
		{
			token = newtoken;
			special_last(&token, &newtoken, after);
		}
		return (1);
	}
	return (0);
}

void	special_before(t_token **token, t_token **newtoken, char *before)
{
	free((*token)->name);
	(*token)->name = before;
	(*token)->type = WORD;
	*newtoken = ft_calloc(1, sizeof(t_token));
	if (!*newtoken)
		return ;
	(*newtoken)->name = ft_strdup(" ");
	(*newtoken)->type = BLANK;
	(*newtoken)->status = NO_QUOTE;
	(*newtoken)->prev = (*token);
	(*newtoken)->next = (*token)->next;
	(*token)->next = (*newtoken);
}

void	special_after(t_token **newtoken, char *after)
{
	(*newtoken)->next->prev = (*newtoken);
	free((*newtoken)->next->name);
	(*newtoken)->next->name = after;
	(*newtoken)->next->type = WORD;
	(*newtoken)->next->status = NO_QUOTE;
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
