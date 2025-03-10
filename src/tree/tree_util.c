/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: breda-si <breda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:48:26 by brendon           #+#    #+#             */
/*   Updated: 2025/03/10 18:10:45 by breda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*free_args_on_error(char **args, int i)
{
	while (i >= 0)
		free(args[i--]);
	free(args);
	return (NULL);
}

void	free_token_list(t_token *head)
{
	t_token	*tmp;

	if (!head)
		return ;
	while (head)
	{
		tmp = head->next;
		free_token(head);
		head = tmp;
	}
}

char	**tokken_to_args(t_token *start)
{
	t_token	*aux;
	char	**args;
	int		i;

	aux = start;
	i = 0;
	while (aux)
	{
		aux = aux->next;
		i++;
	}
	args = malloc(sizeof(char *) * (i + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (start)
	{
		args[i] = ft_strdup(start->name);
		if (!args[i])
			return (free_args_on_error(args, i - 1));
		start = start->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

void	ft_remove_tokens(t_token *aux)
{
	if (aux->prev)
		aux->prev->next = aux->next->next;
	if (aux->next->next)
		aux->next->next->prev = aux->prev;
	free_token(aux->next);
	free_token(aux);
}

void	*handle_redir_error(t_redir *redir, t_minishell *bash, t_token *start)
{
	perror("minishell");
	bash->exit_status = 1;
	free(redir->file_name);
	free(redir);
	free_token_list(start);
	return (NULL);
}
