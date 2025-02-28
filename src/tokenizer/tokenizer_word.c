/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@students.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 16:44:48 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/02/26 18:33:17 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	tokenizer_word(char *line, int i, t_minishell *bash)
{
	int j;
	char *word;

	j = i;
	while (line[i] && ft_isword(line[i]))
		i++;
	word = ft_substr(line, j, i - j);
	if (!word)
		return (0);
	add_tokenlst(&bash, word, WORD, NO_QUOTE);
	return (i - 1);
}

int	ft_isword(char s)
{
	if ((s >= 9 && s <= 13) || s == 32
		|| s == '\'' || s == '"'
		|| s == '|' || s == '$' || s == '>'
		|| s == '<')
		return (0);
	return (1);
}
