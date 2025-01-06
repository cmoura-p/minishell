/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:44:44 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/01/05 09:33:13 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		handle_blank(char *line, int i, t_minishell *bash)
{
	char	*word;

	i = skip_blank(line, i);
	word = ft_strdup(" ");
//	if (!word)				// aqui tem que ver como retornar caso
//		return (0);			// o malloc do ft_strdup nao funcione
	add_tokenlst(&bash, word, BLANK, NO_QUOTE);
	return (i - 1);
}

void	tokenizer(t_minishell *bash)
{
	int i;
	char *line;

	i = 0;
	line = bash->cmd_line;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			i = tokenizer_quotes(line, i, bash);
		else if (line[i] == '|' || line[i] == '$'
				|| line[i] == '<' || line[i] == '>')
			i = tokenizer_metachar(line, i, bash);
		else if (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13))
			i = handle_blank(line, i, bash);
		else
			i = tokenizer_word(line, i, bash);
		if (line[i])
			i++;
	}
}
