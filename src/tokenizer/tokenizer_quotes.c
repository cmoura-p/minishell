/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 16:43:26 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/01/08 11:43:56 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	tokenizer_quotes(char *line, int i, t_minishell *bash)
{
	if (line[i] == '\'')
		i = s_quote(line, i, bash);
	else
		i = d_quote(line, i, bash);
	return (i);
}
int	s_quote(char *line, int i, t_minishell *bash)
{
	int		j;
	char	*quote;

	j = i;
	i++;
	while (line[i])
	{
		if (line[i] == '\'')
			break ;
		i++;
	}
	if (i-j == 1)
		quote = ft_strdup("");
	else
		quote = ft_substr(line, j + 1, i - j - 1);
	if (!quote)
		return (0);
	add_tokenlst(&bash, quote, WORD, SINGLE_Q);
	return (i);
}
int	d_quote(char *line, int i, t_minishell *bash)
{
	int		j;
	char	*quote;

	j = i;
	i++;
	while (line[i])
	{
		if (line[i] == '\"')
			break ;
		i++;
	}
	if (i-j == 1)
		quote = ft_strdup("");
	else
		quote = ft_substr(line, j + 1, i - j - 1);
	if (!quote)
		return (0);
	add_tokenlst(&bash, quote, WORD, DOUBLE_Q);
	return (i);
}
