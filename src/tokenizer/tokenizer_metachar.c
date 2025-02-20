/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_metachar.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 16:44:23 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/02/20 16:02:18 by cmoura-p         ###   ########.fr       */
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
	// aqui tinha um erro grosseiro
	// tava colocando o status = DOUBLE_Q
	// porque eu botei DOUBLE_Q? Nao sei
	// Mas isso jamais permitiria expansao dentro do heredoc
	if (expand_is_hd_eof(line, i, &redir) == 1)			// esse if eh bloco novo
	{
		add_tokenlst(&bash, redir, WORD, NO_QUOTE);
		i = i + ft_strlen(redir);
		return (i-1);
	}
//	redir = ft_substr(line, i, 1);
	if (!redir)
		return (0);
	if (line[i+1] == '_' || ft_isalpha(line[i+1]))
		add_tokenlst(&bash, redir, EXP_ENVP, NO_QUOTE);
	else
		add_tokenlst(&bash, redir, WORD, NO_QUOTE);
	return (i);
}
int	expand_is_hd_eof(char *line, int i, char **redir)
{
	int		j;

	j = i;
	i--;
	while (i >= 0)
	{
		if (line[i] == ' ' || ft_isalpha(line[i]))
			i--;
		else
		{
			if (i != 0)
			{
				if (line[i] == '<' && line[i-1] == '<')
				{
					i = j+1;
					while (line[i] && ft_isword(line[i]))
						i++;
					(*redir) = ft_substr(line, j, i - j);
					return (1);
				}
			}
			i = -1;
		}
	}
	(*redir) = ft_strdup("$");
	return (0);
}
