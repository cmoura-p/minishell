/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@students.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:34:58 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/03/05 16:19:20 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	btw_quotes(char *line, int i)
{
	char	quote;

	quote = line[i];
	i++;
	while (line[i] && line[i] != quote)
		i++;
	if (line[i])
		i++;
	return (i);
}

int	skip_blank(char *line, int i)
{
	while (line[i] && ((line[i] >= 9 && line[i] <= 13) || line[i] == ' '))
		i++;
	return (i);
}

char	*ft_minitrim(char *line)
{
	char	*result;
	int		size;
	int		i;
	int		j;

	size = ft_strlen(line);
	i = skip_blank(line, 0);
	j = size - 1;
	while (line[j] && ((line[j] >= 9 && line[j] <= 13) || line[j] == ' '))
		j--;
	size = j - i + 1;
	result = (char *) malloc(size * sizeof(char) + 1);
	if (!result)
		return (ft_strdup(""));
	j = 0;
	while (line[i] && (j < size))
	{
		result[j] = line [i];
		j++;
		i++;
	}
	result[j] = '\0';
	free(line);
	return (result);
}

void	get_prompt(char **prompt)
{
	char	*pwd;

	pwd = getenv("PWD");
	if (!pwd)
		pwd = "erro pwd ";
	*prompt = ft_strjoin(pwd, ": ");
	if (!(*prompt))
		*prompt = pwd;
}
