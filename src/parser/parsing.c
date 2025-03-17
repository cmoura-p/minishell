/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@students.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:58:23 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/03/17 15:27:48 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parsing(t_minishell *bash)
{
	expandtokens(bash);
	ft_printf("Expandindo \n");
	print_token_list(bash->token);
	if (bash->flag_exp_exit)
		join_exitcode(bash);
	remove_exp_null(bash);
	jointokens(bash);
	ft_printf("Remove NULL e Join \n");
	print_token_list(bash->token);
	set_redir(bash);
	set_commands(bash);
	remove_blank(bash);
	set_arguments(bash);
	ft_printf("Definicao final \n");
	print_token_list(bash->token);
	if (bash->heredoc)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
        signal(SIGTSTP, SIG_IGN);
		heredoc(bash);
		init_signals();
	}
}

void	get_sobra(t_token **aux, char *a_var, char *env_var)
{
	t_token	*newtoken;
	char	*sobra;

	sobra = ft_substr(a_var, (ft_strlen(env_var)), (ft_strlen(a_var) - 1));
	if (sobra && *sobra != '\0')
	{
		newtoken = (t_token *)malloc(sizeof(t_token));
		if (!newtoken)
			return ;
		newtoken->name = sobra;
		newtoken->type = WORD;
		newtoken->status = DOUBLE_Q;
		add_tokenlst_back(&newtoken, *aux);
		newtoken->next = NULL;
	}
	else
		free(sobra);
}

void	join_exitcode(t_minishell *bash)
{
	t_token	*aux;
	t_token	*aux_next;
	t_token	*aux_prev;

	aux = bash->token;
	while (aux)
	{
		aux_next = aux->next;
		aux_prev = aux->prev;
		if (aux->type == EXP_EXIT)
		{
			if ((aux_next) && (aux_next->name != NULL)
				&& (aux_next->type != BLANK))
				join_fw(bash, &aux);
			else
				if ((aux_prev) && (aux_prev->name != NULL)
					&& (aux_prev->type != BLANK))
					join_bw(&aux);
		}
		aux = aux_next;
	}
}

void	join_fw(t_minishell *bash, t_token **aux)
{
	char	*temp;

	temp = ft_strjoin((*aux)->name, (*aux)->next->name);
	free((*aux)->next->name);
	(*aux)->next->name = temp;
	(*aux)->next->type = EXP_EXIT;
	if (!(*aux)->prev)
	{
		bash->token = (*aux)->next;
		(*aux)->next->prev = NULL;
	}
	else
	{
		(*aux)->next->prev = (*aux)->prev;
		(*aux)->prev->next = (*aux)->next;
	}
	if ((*aux)->name)
		free((*aux)->name);
	if ((*aux)->env_null)
		free((*aux)->env_null);
	free(*aux);
}

void	join_bw(t_token **aux)
{
	char	*temp;

	temp = ft_strjoin((*aux)->prev->name, (*aux)->name);
	free((*aux)->prev->name);
	(*aux)->prev->name = temp;
	(*aux)->prev->next = (*aux)->next;
	if ((*aux)->next)
		(*aux)->prev->next = (*aux)->prev;
	if ((*aux)->name)
		free((*aux)->name);
	if ((*aux)->env_null)
		free((*aux)->env_null);
	free(*aux);
}
