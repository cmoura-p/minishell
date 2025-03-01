/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@students.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:58:23 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/03/01 21:01:36 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parsing(t_minishell *bash)
{
	expandtokens(bash);
	remove_exp_null(bash);
	jointokens(bash);
	set_redir(bash);
	set_commands(bash);
	remove_blank(bash);
	set_arguments(bash);
	if (bash->heredoc)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
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
