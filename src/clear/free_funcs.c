/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:44:40 by cmoura-p          #+#    #+#             */
/*   Updated: 2024/12/17 19:44:44 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_necessary(char	**line, t_minishell **bash)
{
	(void) bash;
	free(*line);
	*line = NULL;
	//free_minishell(bash);
}

void	ft_clear_all(t_minishell **bash, char	**line)
{
	(void) bash;
	free(*line);
	//free_minishell(bash);
	rl_clear_history();
	ft_printf("%s", SUCCESS_EXIT);
	exit(EXIT_SUCCESS);
}
