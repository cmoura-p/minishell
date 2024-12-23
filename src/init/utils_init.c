/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:34:58 by cmoura-p          #+#    #+#             */
/*   Updated: 2024/12/23 10:05:06 by cmoura-p         ###   ########.fr       */
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
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
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
