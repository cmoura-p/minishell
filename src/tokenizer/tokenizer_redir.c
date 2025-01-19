/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 11:03:44 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/01/18 23:39:29 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	token_redir(char *line, int i, t_minishell *bash)
{
	if (line[i] == '<')
		{
		if (line[i+1] == '<')
			{
				redir_heredoc(line, i, bash);
				i++;
			}
		else
			redir_in(line, i, bash);
		}
	if (line[i] == '>')
		{
		if (line[i+1] == '>')
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

int	redir_heredoc(char *line, int i, t_minishell *bash)
{
	char	*redir;

//	if (!bash->heredoc)
//		init_heredoc(bash);
	redir = ft_substr(line, i, 2);
	if (!redir)
		return (0);
	add_tokenlst(&bash, redir, HEREDOC, NO_QUOTE);
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

