/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:44:44 by cmoura-p          #+#    #+#             */
/*   Updated: 2024/12/23 12:31:35 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int			token_s_quote(char *line, int i, t_minishell *bash)
{
	(void)line;
	(void)i;
	(void)bash;
	return (0);
}
int			token_d_quote(char *line, int i, t_minishell *bash)
{
	(void)line;
	(void)i;
	(void)bash;
	return (0);
}
int			token_pipe(char *line, int i, t_minishell *bash)
{
	(void)line;
	(void)i;
	(void)bash;
	return (0);
}
int			token_dollar(char *line, int i, t_minishell *bash)
{
	(void)line;
	(void)i;
	(void)bash;
	return (0);
}
int			token_redir_app(char *line, int i, t_minishell *bash)
{
	(void)line;
	(void)i;
	(void)bash;
	return (0);
}
int			token_redir_in(char *line, int i, t_minishell *bash)
{
	(void)line;
	(void)i;
	(void)bash;
	return (0);
}
int			token_redir_out(char *line, int i, t_minishell *bash)
{
	(void)line;
	(void)i;
	(void)bash;
	return (0);
}
int			token_heredoc(char *line, int i, t_minishell *bash)
{
	(void)line;
	(void)i;
	(void)bash;
	return (0);
}
int			token_word(char *line, int i, t_minishell *bash)
{
	(void)line;
	(void)i;
	(void)bash;
	return (0);
}
int			handle_blank(char *line, int i, t_minishell *bash)
{
	(void)line;
	(void)i;
	(void)bash;
	return (0);
}

void	tokens(char *line, t_minishell *bash, int i)
{
	(void)bash;
	while (line[i])
	{
		if (line[i] == '\'')
			i = token_s_quote(line, i, bash);
		else if (line[i] == '\"')
			i = token_d_quote(line, i, bash);
		else if (line[i] == '|')
			i = token_pipe(line, i, bash);
		else if (line[i] == '$')
			i = token_dollar(line, i, bash);
		else if (line[i] == '>' && line[i + 1] == '>')
			i = token_redir_app(line, i, bash);
		else if (line[i] == '<' && line[i + 1] == '<')
			i = token_heredoc(line, i, bash);
		else if (line[i] == '<')
			i = token_redir_in(line, i, bash);
		else if (line[i] == '>')
			i = token_redir_out(line, i, bash);
		else if (line[i] == ' ' || line[i] == '\t')
			i = handle_blank(line, i, bash);
		else
			i = token_word(line, i, bash);
		if (line[i])
			i++;
	}
}
