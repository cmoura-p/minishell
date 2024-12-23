/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 19:47:42 by cmoura-p          #+#    #+#             */
/*   Updated: 2024/12/23 10:41:59 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// incluir funcaode caracteres especiais ?

static int	err_quotes(char *line)
{
	char quote = 0;
	int i = 0;

	while (line[i])
	{
		if ((line[i] == '\'' || line[i] == '\"') && quote == 0)
			quote = line[i]; 			// Aspas abertas
		else if (line[i] == quote)
			quote = 0; 					// Aspas fechadas
		i++;
	}
	if (quote != 0)
	{
		ft_printf("Syntax error: Unmatched '%c'\n", quote);
		return (1);
	}
	return (0);
}
static int	err_pipes(char *line)
{
	int		i;

	i = 0;
	if (line[i] == '|')
		return (1);
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			i = btw_quotes(line, i);
		else
		{
			if (line[i] == '|')
			{
				i = skip_blank(line, i + 1);
				if (line[i] == '\0' || line[i] == '|')
					return (1);
			}
			i++;
		}
	}
	return (0);
}
static int	err_redir(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			i = btw_quotes(line, i);
		else
		{
			if (line[i] == '<' || line[i] == '>')
			{
				if (line[i + 1] == line[i])
					i++;
				i = skip_blank(line, i + 1);
				if (line[i] == '\0' || line[i] == '|')
					return (1);
				else if (line[i] == '<' || line[i] == '>')
					return (1);
			}
			else
				i++;
		}
	}
	return (0);
}
static int	err_special_char(char *line)
{
	char	*special;
	int		i;

	special = "();&!*\\";
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			i = btw_quotes(line, i);
		else
		{
			if (ft_strchr(special, line[i]))
			{
				ft_printf("Syntax error: unexpected special char '%c'\n", line[i]);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

char	*check_syntax(char *cmd_line)
{
	if (!cmd_line)
		return (0);
	cmd_line = ft_strtrim(cmd_line, " ");
	if (err_quotes(cmd_line))
		return(NULL);
	if (err_pipes(cmd_line))
	{
		ft_printf("Syntax error: wrong use of pipes\n");
		return (NULL);
	}
	if (err_redir(cmd_line))
	{
		ft_printf("Syntax error: wrong use of redirection\n");
		return (NULL);
	}
	if (err_special_char(cmd_line))
		return(NULL);
	return (cmd_line);
}

