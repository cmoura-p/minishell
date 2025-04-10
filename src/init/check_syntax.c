/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@students.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 19:47:42 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/04/10 12:23:19 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	err_quotes(char *line)
{
	char	quote;
	int		i;

	quote = 0;
	i = 0;
	while (line[i])
	{
		if ((line[i] == '\'' || line[i] == '\"') && quote == 0)
			quote = line[i];
		else if (line[i] == quote)
			quote = 0;
		i++;
	}
	if (quote != 0)
	{
		ft_printf("Minishell: syntax error Unclosed quotes '%c'\n", quote);
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
				else
					i--;
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
				if (line[i] == '\0' || line[i] == '<' || \
					line[i] == '|' || line[i] == '>')
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
			i = btw_quotes(line, i) - 1;
		else
		{
			if (ft_strchr(special, line[i]))
			{
				ft_printf("Minishell: syntax error special char '%c'\n", \
					line[i]);
				return (1);
			}
		}
		if (line[i] != '\0')
			i++;
	}
	return (0);
}

char	*check_syntax(char *cmd_line)
{
	if (!cmd_line)
		return (0);
	if (err_quotes(cmd_line))
		return (NULL);
	if (err_pipes(cmd_line))
	{
		ft_printf("Minishell: syntax error wrong use of pipes\n");
		return (NULL);
	}
	if (err_redir(cmd_line))
	{
		ft_printf("Minishell: syntax error near unexpected token `newline'\n");
		return (NULL);
	}
	if (err_special_char(cmd_line))
		return (NULL);
	return (cmd_line);
}
