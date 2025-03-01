/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@students.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 11:03:44 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/03/01 20:44:02 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	token_redir(char *line, int i, t_minishell *bash)
{
	if (line[i] == '<')
		redir_in(line, i, bash);
	if (line[i] == '>')
	{
		if (line[i + 1] == '>')
		{
			redir_app(line, i, bash);
			i++;
		}
		else
			redir_out(line, i, bash);
	}
	return (i);
}

int	redir_app(char *line, int i, t_minishell *bash)
{
	char	*redir;

	redir = ft_substr(line, i, 2);
	if (!redir)
		return (0);
	add_tokenlst(&bash, redir, REDIR_APP, NO_QUOTE);
	return (i);
}

int	redir_in(char *line, int i, t_minishell *bash)
{
	char	*redir;

	redir = ft_substr(line, i, 1);
	if (!redir)
		return (0);
	add_tokenlst(&bash, redir, REDIR_IN, NO_QUOTE);
	return (i);
}

int	redir_out(char *line, int i, t_minishell *bash)
{
	char	*redir;

	redir = ft_substr(line, i, 1);
	if (!redir)
		return (0);
	add_tokenlst(&bash, redir, REDIR_OUT, NO_QUOTE);
	return (i);
}
