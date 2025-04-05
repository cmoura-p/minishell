/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@students.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:34:58 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/03/23 09:25:46 by cmoura-p         ###   ########.fr       */
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

char	*ft_minitrim(char *line, int i, int j)
{
	char	*result;
	int		size;

	size = strlen(line);
	i = 0;
	while (line[i] && ((line[i] >= 9 && line[i] <= 13) || line[i] == ' '))
		i++;
	j = size - 1;
	while (j >= i && ((line[j] >= 9 && line[j] <= 13) || line[j] == ' '))
		j--;
	if (j >= i)
		size = j - i + 1;
	else
		size = 0;
	result = (char *)malloc((size + 1) * sizeof(char));
	if (!result)
		return (strdup(""));
	ft_strlcpy(result, line + i, size + 1);
	result[size] = '\0';
	free(line);
	return (result);
}
