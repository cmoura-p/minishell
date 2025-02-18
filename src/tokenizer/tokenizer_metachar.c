/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_metachar.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 16:44:23 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/02/18 00:29:35 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	tokenizer_metachar(char *line, int j, t_minishell *bash)
{
	int i;

	if (line[j] == '|')
		i = token_pipe(line, j, bash);
	if (line[j] == '$')
		i = token_dollar(line, j, bash);
	if (line[j] == '<' && line[j+1] == '<')
		i = token_heredoc(line, j, bash);
	else if (line[j] == '<' || line[j] == '>')
		i = token_redir(line, j, bash);
	return (i);
}
int	token_pipe(char *line, int i, t_minishell *bash)
{
	char	*redir;

	redir = ft_substr(line, i, 1);
	if (!redir)
		return (0);
	add_tokenlst(&bash, redir, PIPE, NO_QUOTE);
	return (i);
}
int	token_dollar(char *line, int i, t_minishell *bash)
{
	char	*redir;
	
	if (line[i+1] == '?')
	{
		redir = ft_substr(line, i, 2);
		if (!redir)
			return (0);
		add_tokenlst(&bash, redir, EXP_EXIT, NO_QUOTE);
		return (i+1);
	}
	redir = ft_substr(line, i, 1);
	if (!redir)
		return (0);
	if (line[i+1] == '_' || ft_isalpha(line[i+1]))
		add_tokenlst(&bash, redir, EXP_ENVP, NO_QUOTE);
	else
		add_tokenlst(&bash, redir, WORD, NO_QUOTE);
	return (i);
}
