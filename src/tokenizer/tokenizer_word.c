/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 16:44:48 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/01/18 23:37:41 by cmoura-p         ###   ########.fr       */
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
	if (!word)				// verificar o retorno no erro
		return (0);			// do malloc no substr
	add_tokenlst(&bash, word, WORD, NO_QUOTE);
	return (i - 1);
}
