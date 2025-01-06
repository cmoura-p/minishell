/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:34:58 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/01/04 21:00:59 by cmoura-p         ###   ########.fr       */
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
char	**load_envp(char **envp)
{
	int		i;
	char	**envp_aux;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
		i++;
	envp_aux = ft_calloc(sizeof(char *), i + 1);
	if (!envp_aux)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		envp_aux[i] = ft_strdup(envp[i]);
		i++;
	}
	return (envp_aux);
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
		return (NULL);
	j = 0;
	while (line[i] && (j < size))
	{
		result[j] = line [i];
		j++;
		i++;
	}
	result[j] = '\0';
	return (result);
}
